 /*
NAIVE BAYES CLASSIFIER
IMPLEMENTING NAIVE BAYES CLASSIFIER for a given training data set and for a particular instance
------------------------------------------------------------------------------------------------------------------

Deciding if one should play tennis under certain circumstances:
-------------------------------------------------------------------------------------------------------------------

Training Example Data Set
Outlook	    Temperature 	Humidity	Wind	    Play
Sunny	    Hot	            High	    Weak	    No
Sunny	    Hot	            High	    Strong	    No
Overcast	Hot	            High	    Weak	    Yes
Rainy	    Mild	        High	    Weak	    Yes
Rainy	    Cool	        Normal	    Weak	    Yes
Rainy	    Cool	        Normal	    Strong	    No
Overcast	Cool	        Normal	    Strong	    Yes
Sunny	    Mild	        High	    Weak	    No
Sunny	    Cool	        Normal	    Weak	    Yes
Rainy	    Mild	        Normal	    Weak	    Yes
Sunny	    Mild	        Normal	    Strong	    Yes
Overcast	Mild	        High	    Strong	    Yes
Overcast	Hot	            Normal	    Weak	    Yes
Rainy	    Mild	        High	    Strong	    No
--------------------------------------------------------------------------------------------------------------------

To Calculate :-
P(C|X1,X2,�,Xn)=P(X1,X2,�,Xn|C)P(C)/P(X1,X2,�,Xn)
--------------------------------------------------------------------------------------------------------------------

We calculate the following-

P(Play =Yes)
P(Play=No)


P(Outlook=X1|Play=Yes)
P(Temperature=X2|Play=Yes)
P(Humidity=X3|Play=Yes)
P(Wind=X4|Play=Yes)

P(Outlook=X1|Play=No)
P(Temperature=X2|Play=No)
P(Humidity=X3|Play=No)
P(Wind=X4|Play=No)

P(Yes | <X1,X2,X3,X4>) = P(Yes)* P(X1|Yes)*P(X2|Yes) *P(X3|Yes)* P(X4|Yes)
P(No | <X1,X2,X3,X4>) = P(No)* P(X1|No)*P(X2|No) *P(X3|No)* P(X4|No)

We now have P(X1,X2,�,Xn|C)P(C)

We now need to divide the results by the evidence i.e.P(X)

P(X)=P(Outlook=X1)*P(Temperature=X2)*P(Humidity=X3)*P(Wind=X4)

and see whose probability has the highest value. That is our probability.
-------------------------------------------------------------------------------------------------------------------
*/
#include <string.h>
#include <stdio.h>
#include <time.h>
// parse the data csv file and store into array of struct
typedef struct key_value
{

    char outlook[15];
    char temperature[15];
    char humidity[15];
    char wind[15];
    char play[15];
} dict;

int main()
{
    //intializing file pointer
    FILE *fp =fopen("n_b_dataset.csv", "r");
    if(!fp)
    {

        printf("Error occurred");
        return 0;
    }

    char buff[1024]; // stores first 1024 lines into buffer
    int row_count =0;
    int field_count=0;

    dict values[14]; //array to struct to store values

    int i=0;
    while(fgets(buff,1024,fp))
    {

        //printf("%s\n",buff);//this passes all the data
        field_count=0;
        row_count++;
        if(row_count==1)
            continue; //skipping the heading lines

        char *field =strtok(buff,",");

        while(field)
        {
            if(field_count == 0)
                strcpy(values[i].outlook,field);
            if(field_count == 1)
                strcpy(values[i].temperature,field);
            if(field_count == 2)
                strcpy(values[i].humidity,field);
            if(field_count == 3)
                strcpy(values[i].wind,field);
            if(field_count == 4)
                strcpy(values[i].play,field);

            field= strtok(NULL,",");
            field_count++;
        }
        i++;
    }
    fclose(fp);
    //printf("\nWe consider the given instance-");
    //printf("\nX = (Outlook=Sunny, Temperature =Cool, Humidity = High, Wind = Strong)\n");
    char atr1[20],atr2[20],atr3[20],atr4[20];

    int choice;
    while(1)
    {
        printf("\n********************************");
        printf("\n1.Print the training dataset\n");
        printf("2.Making the predicition\n");
        printf("3.Result\n");
        printf("4.Exit\n");
        printf("*********************************\n");
        printf("Enter your choice : ");

        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printValues(values);
            break;
        case 2:
            printf("\nLet us predict if one can play tennis under the specified instance");
            printf("\n1.Enter the value of Outlook. \nChoose between(Sunny/Rainy/Overcast)\n");
            scanf("%s", atr1);
            printf("\n2.Enter the value of Temperature. \nChoose between(Hot/Mild/Cool)\n");
            scanf("%s", atr2);
            printf("\n3.Enter the value of Humidity. \nChoose between(High/Normal)\n");
            scanf("%s", atr3);
            printf("\n4.Enter the value of Wind. \nChoose between(Weak/Strong)\n");
            scanf("%s", atr4);

            int total=14;
            int yes,a1_yes,a2_yes,a3_yes,a4_yes;
            double p_yes,pa1_yes,pa2_yes,pa3_yes,pa4_yes,p_x,p_instance_yes,p_instance_no,num_yes,num_no;//indicates the probabilitie

            yes=probab_yes(values);
            p_yes= (double)yes/total;

            a1_yes=outlook_yes(values,atr1);
            pa1_yes = (double)a1_yes/yes;

            a2_yes=temp_yes(values,atr2);
            pa2_yes = (double)a2_yes/yes;

            a3_yes=humidity_yes(values,atr3);
            pa3_yes =(double)a3_yes/yes;

            a4_yes=wind_yes(values,atr4);
            pa4_yes =(double)a4_yes/yes;

            num_yes=pa1_yes*pa2_yes*pa3_yes*pa4_yes*p_yes;

            int no = total-yes;
            int a1_no,a2_no,a3_no,a4_no;
            double p_no,pa1_no,pa2_no,pa3_no,pa4_no;//indicates the probability variables
            p_no= (double)no/total;

            a1_no=outlook_no(values,atr1);
            pa1_no = (double)a1_no/no;

            a2_no=temp_no(values,atr2);
            pa2_no = (double)a2_no/no;

            a3_no=humidity_no(values,atr3);
            pa3_no =(double)a3_no/no;

            a4_no=wind_no(values,atr4);
            pa4_no =(double)a4_no/no;

            num_no=pa1_no*pa2_no*pa3_no*pa4_no*p_no;

            // calculating for P(X)
            int a1,a2,a3,a4;
            double p_a1,p_a2,p_a3,p_a4;

            a1=count_a1(values,atr1);
            p_a1=(double)a1/total;

            a2=count_a2(values,atr2);
            p_a2=(double)a2/total;

            a3=count_a3(values,atr3);
            p_a3=(double)a3/total;

            a4=count_a4(values,atr4);
            p_a4=(double)a4/total;

            p_x=p_a1*p_a2*p_a3*p_a4;
            //probability= num/p_x


            p_instance_yes=(num_yes)/p_x;
            p_instance_no =(num_no)/p_x;

            printf("\nProbability of (Play=Yes|X) is %f \nProbability of (Play=No|X) is %f\n",p_instance_yes,p_instance_no);
            break;

            case 3:
             printf("\nX = (Outlook=%s, Temperature =%s, Humidity = %s, Wind = %s)\n",atr1,atr2,atr3,atr4);
            if(p_instance_yes>p_instance_no)
                printf("\nSince, probability of YES i.e. %f is GREATER than %f we CAN PLAY a game of tennis today considering the specified instance.\n",p_instance_yes,p_instance_no);
            else
                printf("\nSince, probability of NO i.e. %f is GREATER than %f we CAN'T PLAY a game of tennis today considering the specified instance.\n",p_instance_no,p_instance_yes);
            break;
        case 4:
            exit(1);
        default:
            printf("Wrong choice\n");
        }/*End of switch*/
    }/*End of while*/


    return 0;
}

void printValues(dict values[])
{
    printf("Outlook   | Temperature| Humidity |  Wind     |  Play\n");
    printf("----------------------------------------------------\n");
    for(int i=0; i<14; i++)
    {
        printf("%-9s | %-10s | %-8s | %-9s | %s",values[i].outlook,values[i].temperature,values[i].humidity,values[i].wind,values[i].play);
    }
}

int probab_yes(dict values[])
{
    int count=0;
    int result;
    char str1[]="Yes";
    for(int i=0; i<14; i++)
    {

        result=strcmp(str1,values[i].play);
        if(result==-1)

            ++count;

    }
    return count;
}

int outlook_yes(dict values[],char* attribute)
{
    int count=0;
    int result,check_yes;
    char str[]="Yes";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].outlook);
        if(result==0)
        {
            check_yes=strcmp(str,values[i].play);
            if(check_yes==-1)
                ++count;
        }
    }
    return count;

}
int temp_yes(dict values[],char* attribute)
{
    int count=0;
    int result,check_yes;
    char str[]="Yes";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].temperature);
        if(result==0)
        {
            check_yes=strcmp(str,values[i].play);
            if(check_yes==-1)
                ++count;
        }

    }
    return count;
}
int humidity_yes(dict values[],char* attribute)
{
    int count=0;
    int result,check_yes;
    char str[]="Yes";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].humidity);
        if(result==0)
        {
            check_yes=strcmp(str,values[i].play);
            if(check_yes==-1)
                ++count;
        }

    }
    return count;
}
int wind_yes(dict values[],char* attribute)
{
    int count=0;
    int result,check_yes;
    char str[]="Yes";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].wind);
        if(result==0)
        {
            check_yes=strcmp(str,values[i].play);
            if(check_yes==-1)
            {
                ++count;
            }
        }
    }
    return count;
}

int outlook_no(dict values[],char* attribute)
{
    int count=0;
    int result,check_no;
    char str[]="No";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].outlook);
        if(result==0)
        {
            check_no=strcasecmp(str,values[i].play);
            if(check_no==-10)
                ++count;
        }
    }
    return count;
}

int temp_no(dict values[],char* attribute)
{
    int count=0;
    int result,check_no;
    char str[]="No";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].temperature);
        if(result==0)
        {
            check_no=strcasecmp(str,values[i].play);
            if(check_no==-10)

                ++count;
        }
    }
    return count;
}

int humidity_no(dict values[],char* attribute)
{

    int count=0;
    int result,check_no;
    char str[]="No";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].humidity);
        if(result==0)
        {
            check_no=strcasecmp(str,values[i].play);
            if(check_no==-10)
                ++count;
        }
    }
    return count;
}

int wind_no(dict values[],char* attribute)
{

    int count=0;
    int result,check_no;
    char str[]="No";
    for(int i=0; i<14; i++)
    {
        result=strcmp(attribute,values[i].wind);
        if(result==0)
        {
            check_no=strcasecmp(str,values[i].play);
            if(check_no==-10)
                ++count;
        }
    }
    return count;
}

int count_a1(dict values[],char* atr)
{
    int count=0;
    int result;
    for(int i=0; i<14; i++)
    {
        result=strcmp(atr,values[i].outlook);
        if(result==0)
            count++;
    }
    return count;
}
int count_a2(dict values[],char* atr)
{
    int count=0;
    int result;
    for(int i=0; i<14; i++)
    {
        result=strcmp(atr,values[i].temperature);
        if(result==0)
        {
            ++count;
        }
    }
    return count;
}

int count_a3(dict values[],char* atr)
{
    int count=0;
    int result;
    for(int i=0; i<14; i++)
    {
        result=strcmp(atr,values[i].humidity);
        if(result==0)
        {
            ++count;
        }
    }
    return count;
}

int count_a4(dict values[],char* atr)
{
    int count=0;
    int result;
    for(int i=0; i<14; i++)
    {
        result=strcmp(atr,values[i].wind);
        if(result==0)
        {
            ++count;
        }
    }
    return count;
}
