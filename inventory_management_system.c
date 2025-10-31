#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Inventory
{
    int id;
    char name[100];
    int quantity;
    float price;	
};

void addProducts();
void displayProducts();
void serchProductByname();
void sortProduct();
void searchByid();



int main()
{
	int choice;

	do
	{
		printf("\n===== Ineventory Management System =====\n");
		printf("1. Add your product\n");
		printf("2. Show All Product\n");
		printf("3. Search Product By Name\n");
		printf("4. Sort Product List\n");
		printf("5. Search Product by ID\n");
		printf("6. Exit\n");
		printf("Enter your Choice\n");
		scanf("%d",&choice);

		switch (choice)
		{
		    case 1:
		    	addProducts();
		    	break;
		    case 2:
		    	displayProducts();
		    	break;
		    case 3:
		    	serchProductByname();
		    	break;
		    case 4:
		    	sortProduct();
		    	break;
			case 5:
			    searchByid();
				break;
		    case 6:
		    	exit(0);
		    default:
		    	printf("Invalid Choice\n");
		}

	}
	while(1);
}

void addProducts()
{
	FILE *fp = fopen("Inventory.dat","ab");
	if(!fp)
	{
		printf("Record Not Found\n");
		return;
	}

	struct Inventory I;

	printf("Enter Product Id\n");
	scanf("%d",&I.id);
	printf("Enter Product Name\n");
	scanf("%s",I.name);
	printf("Enter Products Quantity\n");
	scanf("%d",&I.quantity);
	printf("Enter Product Price\n");
	scanf("%f",&I.price);

	fwrite(&I,sizeof(struct Inventory),1,fp);
	fclose(fp);
}

void displayProducts()
{
	FILE *fp = fopen("Inventory.dat","rb");
	if(!fp)
	{
		printf("No records found\n");
		return;
	}

	struct Inventory I;

	printf("\nID\tName\tQuantity\tPrice\n");
	printf("---------------------------------------\n");

	while(fread(&I,sizeof(struct Inventory),1,fp))
	{
		printf("%d\t%s\t%d\t%.2f\n",I.id,I.name,I.quantity,I.price);
	}

	fclose(fp);
}

void serchProductByname()
{
	FILE *fp = fopen("Inventory.dat","rb");
	if(!fp)
	{
		printf("No records found\n");
		return;
	}

	struct Inventory I;

	char name[50];
	printf("Enter Product Name\n");
	scanf("%s",name);

	int found=0;
	int i=1;
	while(fread(&I,sizeof(struct Inventory),1,fp))
	{
		if(strstr(I.name,name)!=NULL)
		{
			printf("Found %d: %d %s %d %.2f\n",i,I.id,I.name,I.quantity,I.price);
			found=1;
			i++;
		}
	}
	if(!found)
	{
		printf("No Products Found\n");
	}

	fclose(fp);
}

int sortByprice(const void *a, const void *b)
{
	struct Inventory *x = (struct Inventory *)a;
	struct Inventory *y = (struct Inventory *)b;

	if(x->price > y->price)
	{
		return 1;
	}
	else if (x->price < y->price)
	{
		return -1;
	}
	else
	{
		return 0;
	}	
}

int sortByquantity(const void *a, const void *b)
{
	struct Inventory *x = (struct Inventory *)a;
	struct Inventory *y = (struct Inventroy *)b;
    return x->quantity - y->quantity;
}

char sortByname(const void *a, const void *b)
{
	struct Inventory *x = (struct Inventory *)a;
	struct Inventory *y = (struct Inventory *)b;
	return strcmp(x->name,x->name);
}

int usingSlectionsort(struct Inventory list[100],int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=i+1; j<n; j++)
		{
			if(list[i].quantity < list[j].quantity)
			{
				struct Inventory temp= list[i];
				list[i] = list[j];
				list[j]=temp;
			}
		}
	}
}

void sortProduct()
{
	FILE *fp = fopen("Inventory.dat","rb");
	if(fp==NULL)
	{
		printf("     Inventory is  Empty     \n");
		printf("----No Records Found----\n");
		return;
	}
    
    struct Inventory I;
	struct Inventory list[100];
	int count=0;
	while(fread(&list[count],sizeof(struct Inventory),1,fp))
	{
		count++;
	}
	fclose(fp);

	int first_choice;
	printf("First choose which sort you want to Implement\n");

	printf("1. Using Selection Sort\n");
	printf("2. Using qsort\n");
	printf("Enter your Choice: ");
	scanf("%d",&first_choice);
    
	switch (first_choice)
	{
	case 1:
		usingSlectionsort(list,count);
		break;
	case 2:
	{
	    int choice;
	    printf("\nSort by:\n1.Price\n2.Quantity\n3.Name\nEnter your Choice: ");
	    scanf("%d",&choice);
        
	    switch (choice)
	    {
	    case 1:
	    	qsort(list,count,sizeof(struct Inventory),sortByprice);
	    	break;
	    case 2:
	        qsort(list,count,sizeof(struct Inventory),sortByquantity);
	    	break;
	    case 3:
	        qsort(list,count,sizeof(struct Inventory),sortByname);
	    	break;
	    default:
	    	printf("Inavalid Choice\n");
	    	return;
	    }
	        break;
	}		
	default:
		printf("Invalid Choice\n");
		return;
	}

	printf("\nThe sorted List of based on Quantity\n");
	printf("\nId\tName\tQuantity\tPrice\n");
	printf("\n----------------------------------------\n");

	for(int i=0; i<count; i++)
	{
		printf("%d\t%s\t%d\t%.2f\n",list[i].id,list[i].name,list[i].quantity,list[i].price);
	}
}

void searchByid()
{
	FILE *fp = fopen("Inventory.dat","rb");
	if(fp == NULL)
	{
		printf("No records Founds\n");
		return;
	}

	struct Inventory I;
	int id;
	int found = 0;
	printf("Enter an ID for search a product: ");
	scanf("%d",&id);
    int i =1;
	while(fread(&I,sizeof(struct Inventory),1,fp))
	{
		if(I.id==id)
		{
			printf("Found %d: %d %s %d %.2f\n",i,I.id,I.name,I.quantity,I.price);
			found=1;
			i++;
		}
	}
    fclose(fp);

	if(found==0)
	{
		printf("No Products Found\n");
	}
}