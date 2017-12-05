#include "csapp.h"

/* Psize - page size, MAX_OFF - max offset */
#define Psize 0x1000
#define MAX_OFF 0x1000000

/* 
 * flag is just used to read an address. Otherwise the compiler may optmize
 * my poor 'visit' function.
 */
int flag;

/* the buffer for the siglongjmp */
sigjmp_buf buf;

/* visit - to inform an address */
void visit(unsigned long ptr)
{
	if (*(char *)ptr == 'A')
		flag = 1;
}

/* print - print the map information for comparing */
void print()
{
	char basePath[1000];
	memset(basePath, '\0', sizeof(basePath));
	strcpy(basePath, "/proc/");
	char temp[100];
	int pid = getpid();
	sprintf(temp, "%d", pid);
	strcat(basePath, temp);
	strcat(basePath, "/maps");
	int fd = open(basePath, O_RDONLY, 0);
	char *cs = (char *)mmap(NULL, 2, PROT_READ, MAP_SHARED, fd, 0);
	char c;
	while(read(fd, &c, 1) != 0)
		if (write(STDOUT_FILENO, &c, 1) == -1)
			exit(1);
	close(fd);
	return;
}

/* sigsegv_handler - to set the behaviour when receiving the SIGSEGV signal */
void sigsegv_handler(int sig)
{
	siglongjmp(buf, 1);
}

int main(int argc, char **argv)
{
    int fd;
    void *ptr;
    unsigned long adr;
    unsigned long offset;
    unsigned long heap_bottom;
    
	signal(SIGSEGV, sigsegv_handler);
	
	/* Get the brk of heap */  
	ptr = sbrk(0);
	
    /* Get the bottom of heap */	 
	heap_bottom = ((unsigned long)ptr) & (~0xfff);
	if (sigsetjmp(buf, 1) == 0)
	{
	    while (1)
	    {
	        visit(heap_bottom);
            heap_bottom -= Psize;
	    }
	}
		
	/* 1.Read the .text .data .bss */
	printf("\n.text .data .bss\n");
	adr = 0x400000;
	for (; adr < heap_bottom; adr += Psize)
	{
		if (sigsetjmp(buf, 1) == 0)
		{
			visit(adr);
		    printf("%08lx-", adr);
		    for (; adr < heap_bottom; adr += Psize)
		    {
		        visit(adr);
		        if (sigsetjmp(buf, 1) == 1)
		            break;
		    }
			printf("%08lx\n", adr);
			adr -= Psize;
		}
	}
	
	/* 2.Read the [heap] */
	printf("\n[heap]\n");
    adr = heap_bottom;
    printf("%08lx-", adr);
	for (offset = 0; ; offset += Psize)
	{
	    visit(adr + offset);
		if (sigsetjmp(buf, 1) == 1)
		    break;
	}
	printf("%08lx\n", adr + offset);
	
	/* 3.Read the shared lib */
	printf("\nshared lib\n");
	
	/* mmap an area then munmap it, to get the address of shared lib */
	fd = open("1", O_CREAT, S_IROTH);
	ptr = mmap(NULL, 1, PROT_READ, MAP_PRIVATE, fd, 0);
	munmap(ptr, 1);
	close(fd);
	
    adr = (unsigned long)ptr & (~0xfff);
    adr -= MAX_OFF;
    for (offset = 0; offset < 2 * MAX_OFF; offset += Psize)
    {
  	    if (sigsetjmp(buf, 1) == 0)
	    {
	        visit(adr + offset);
	       	printf("%lx-", adr + offset);
	        for (;offset < 2 * MAX_OFF; offset += Psize)
	        {
	            visit(adr + offset);
	            if (sigsetjmp(buf, 1) != 0)
	                break;
	        }
	        printf("%lx\n", adr + offset);
	        offset -= Psize;
	    }      
    }
    
    /* 4.Read the [stack] */
    printf("\n[stack]\n");
    adr = (unsigned long)(&argc) & (~0xfff);
    
    /* Get the stack top first */
	if (sigsetjmp(buf, 1) == 0)
	{
	    while (1)
	    {
	        visit(adr);
            adr -= Psize;
	    }
	}
	
	/* Then trace to the high address */
	for (offset = Psize; ; offset += Psize)
	{
		if (sigsetjmp(buf, 1) == 0)
		{
			visit(adr + offset);
		    printf("%lx-", adr + offset);
		    for (; offset <= MAX_OFF; offset += Psize)
		    {
		        visit(adr + offset);
		        if (sigsetjmp(buf, 1) == 1)
		            break;
		    }
			printf("%lx\n", adr + offset);
			offset -= Psize;
		}
		else
		    break;
	}
	
	printf("\n");
	if (flag)
	    printf("\n");
	
	/* At last, print the maps to compare */
	print();
	return 0;
}
