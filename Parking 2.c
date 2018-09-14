#include <stdio.h>
#include <stdlib.h>

int mutex=1,full=0,empty=5,x=0;
char a[5]={'-','-','-','-','-'};

void display()
{
    printf("\t\t\tPARKING SYSTEM\n\n");
    printf("The parking lot contains 5 parkings, a car can be parked at any of the 5 parkings \nas per the car owner's will\n");
    printf("Similarly car from any parking can be parked out \n");
    printf("Press 1 to park a car\nPress 2 to park out a car\nPress 3 to exit\n\n");
}

int parking(int q)
{
    int i;
    int y=0;
    if(a[q]=='*')
    {
        printf("Car is already parked.\n");
        y=1;
        return y;
    }
    else
    {
        a[q]='*';
        for(i=0;i<5;i++)
        {
            printf("%c",a[i]);
        }
    }
    printf("\n");
    return y;
}

int parking_out(int q)
{
    int i;
    int y=0;
    if(a[q]=='-')
    {
        printf("Parking slot is already empty.\n");
        y=1;
        return y;
    }
    else
    {
        a[q]='-';
        for(i=0;i<5;i++)
        {
            printf("%c",a[i]);
        }
    }
    printf("\n");
    return y;
}

int main()
{
    display();
    int n;
    void entry();
    void exit1();
    int wait(int);
    int signal(int);
    while(1)
    {
        printf("Enter your choice: ");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                if((mutex==1) && (empty!=0))
                {
                    entry();
                }
                else
                    printf("Parking is full !!\n\n");
                break;
            case 2: if((mutex==1) && (full!=0))
                    {
                        exit1();
                    }
                    else
                    {
                        printf("Parking is Empty !!\n\n");
                    }
                    break;
            case 3: exit(0);
                    break;
        }
    }
    return 0;
}

int wait(int s)
{
    return(--s);
}
int signal(int s)
{
    return(++s);
}
void entry()
{
    int p;
    mutex=wait(mutex);

    printf("Where do you want to park ?? ");
    scanf("%d",&p);
    int k=parking(p-1);
    if(k==1)
    {
        printf("Number of cars parked = %d\n",x);
    }
    else
    {
        full=signal(full);
        empty=wait(empty);
        x++;
        printf("Number of cars parked = %d\n",x);
    }
    printf("\n");
    mutex=signal(mutex);
}

void exit1()
{
    int s;
    mutex=wait(mutex);

    printf("Which Car is parking out ?? ");
    scanf("%d",&s);
    int k=parking_out(s-1);
    if(k==1)
    {
        printf("Number of cars left = %d\n",x);
    }
    else
    {
        full=wait(full);
        empty=signal(empty);
        x--;
        printf("Number of cars left = %d\n",x);
    }
    printf("\n");
    mutex=signal(mutex);
}
