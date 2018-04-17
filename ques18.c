#include<stdio.h>                                                  

int count=0;
int count1=0;                                                     
 
struct student 										
{
	int id;
	float arrival_time;
	float waiting_time;
	float burst_time;
	float completion_time;
	int index;
	int no;
};

struct teacher                                                      
{
	int id;
	float arrival_time;
	float waiting_time;
	float completion_time;
	float burst_time;
	int index;
	int no;
};

void get_teacher(struct teacher *t, int m)                          
{
	int k;
	for(k=0;k<m;k++)
	{
		printf("\nEnter Teacher id             -     ");
		scanf("%d",&t[k].id);
		printf("Arrival Time                 -     "); 
		scanf("%f",&t[k].arrival_time);
		printf("Time taken at the counter    -     ");
		scanf("%f",&t[k].burst_time);
		t[k].no=k+1;
	}
}

void get_student(struct student *s,int n)                           
{
	int k;
	for(k=0;k<n;k++)
	{
		printf("\nEnter Student id             -     ");
		scanf("%d",&s[k].id); 
		printf("Arrival Time                 -     "); 
		scanf("%f",&s[k].arrival_time);
		printf("Time taken at the counter    -     ");
		scanf("%f",&s[k].burst_time);
		s[k].no=k+1;
	}

}

void scheduling(struct teacher *t, int m, struct student *s, int n, int time)     
{
	int i,j=0,k=0;
	for(i=0;i<m+n;i++)                                                        
	{
		int flag=0;
		if( m!=0 && k+1<=n && s[k].arrival_time<t[j].arrival_time && time<=s[k].arrival_time && s[k].arrival_time!=t[j].arrival_time )  
		{
			flag=1;
		}	
		if(n==0 || (time-t[j].arrival_time>=30 && time-s[k].arrival_time>=30))
		{
			count=0;
		}
		if(k+1<=n)
		{
			count=time-s[k].arrival_time;
		}
		if(m!=0 && (count<=30 || count1==1) && j<m && flag==0) 
		{
			if(t[j].arrival_time>=time)
			{
				t[j].waiting_time=0;
			}
			else
			{
				t[j].waiting_time=time-t[j].arrival_time;
			}
			t[j].completion_time=t[j].waiting_time+t[j].burst_time+t[j].arrival_time;
			count=count+ t[j].burst_time;
			count1++;
			time=t[j].completion_time;
			t[j].index=i;
			j++;
		}
		else if(n!=0 && k<n )
		{
			if(s[k].arrival_time>=time)
			{
				s[k].waiting_time=0;
			}
			else
			{
				s[k].waiting_time=time-s[k].arrival_time;
			}
			s[k].completion_time=s[k].waiting_time+s[k].burst_time+s[k].arrival_time;
			count=0;
			count1=0;
			time=s[k].completion_time;
			s[k].index=i;
			k++;
		}
	}
}

void display(struct teacher *t, int m, struct student *s, int n)                
{
	int i,k=0,j=0;
	printf("\n  Sequence    Id           Visitor      Arrival Time       Waiting Time       Time Taken      Completion Time");
	printf("\n                                                                             at the counter      ");	
	for(i=0;i<m+n;i++)
	{
		if(t[j].index==i && m!=0)
		{
			printf("\n%4d%12d          Teacher %d%14.1f%19.1f%18.1f%18.1f",t[j].index+1,t[j].id,t[j].no,t[j].arrival_time,t[j].waiting_time,t[j].burst_time,t[j].completion_time);
			j++;
		}
		else if(s[k].index==i && n!=0)
		{
			printf("\n%4d%12d          Student %d%14.1f%19.1f%18.1f%18.1f",s[k].index+1,s[k].id,s[k].no,s[k].arrival_time,s[k].waiting_time,s[k].burst_time,s[k].completion_time);
			k++;
		}
	}
}

void teacher_sort(struct teacher *t, int m)                           
{
	struct teacher temp;
	int i,j;
	for (i=0;i<m;++i) 
	{
        for (j=i+1;j<m;++j)
        {
            if (t[i].arrival_time > t[j].arrival_time) 
            {
                temp =  t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }	
}

void student_sort(struct student *s, int n)                           
{
	struct student temp;
	int i,j;
	for (i=0;i<n;++i) 
	{
        for (j=i+1;j<n;++j)
        {
            if (s[i].arrival_time > s[j].arrival_time) 
            {
                temp =  s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }	
}

main()                                                               
{
	int m,n=0;
	printf("\nEnter number of teachers in queue - ");
	scanf("%d",&m);
	printf("\nEnter number of students in queue - ");
	scanf("%d",&n);
	
	struct student s[n];                                            
	struct teacher t[m];                                            

	get_teacher(t,m);									

	get_student(s,n);                                              
	
	teacher_sort(t,m);                                            
	
	student_sort(s,n);                                            
	
	scheduling(t,m,s,n,0);                                      

	display(t,m,s,n);                                           
	printf("\n\n");
}
