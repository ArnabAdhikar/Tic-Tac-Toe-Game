//by arnab anderston
# include<stdio.h>
# include<string.h>
# include <stdlib.h>	
# define true 0
# define false 1
struct product{
		char id[10];        // product code/no.
		char name[20];      // product name
		int  quantity;      // remaining quantity of product. Subtract from the original quantity the quantity purchased
        int  numSold;       // initially zero, when no purchase yet.
		float price;        // price of one piece of product
		int discount;       // discount for this product
		float sales;        // accumulated sales, total sales for this product
    };
struct product prod[30];
int count = 0;
FILE *f;
int writefile(){
    int i;
    f = fopen("inventory.txt", "w");
    if (f == NULL)
        return -1;			
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; ++i){
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].discount);
        fprintf(f, "%f\n", prod[i].sales);
    }
    fclose(f);
    return 0;
}
int readFile(){
    int n = 0;
    int i;
    f = fopen("inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; ++i){
        fgets(prod[i].id, 10, f);
        prod[i].id[strlen(prod[i].id) - 1] = 0; // remove new lines
        fgets(prod[i].name, 20, f);
        prod[i].name[strlen(prod[i].name)-1] = 0; // remove new lines
        fscanf(f, "%d", &prod[i].quantity);
        fscanf(f, "%d", &prod[i].numSold);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%d", &prod[i].discount);
        fscanf(f, "%f\n", &prod[i].sales);
    }
    fclose(f);
    return n;
}
void disZeroQuant(){
	int i;
    count= readFile();	// call the read function
    printf("\nProducts with zero Quantity: ");
    for (i=0; i<count; i++){
		if(prod[i].quantity==0){
            printf("\nName of the product: %s \nProduct Id: %s \nQuantity left: %d \nNumber of product sold: %d \nPrice of the product: %.2f \nDiscount of the product: %d %% \nTotal Sales: %.2lf\n",
            prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
		    }
    }
    writefile();	
}
void dispHsale(){
	int high,i;
	high=prod[0].numSold;
    for(i=0;i<count;i++){
        if(prod[i].numSold>high)
        high=prod[i].numSold;
    }
    printf("\nThe Highest Product Sale is: \n");
   	for(i=0;i<count;i++){
        if(prod[i].numSold==high){
            printf("Name of the product: %s \nProduct Id: %s \nQuantity left: %d \nNumber of product sold: %d \nPrice of the product: %.2f \nDiscount of the product: %d %% \nTotal Sales: %.2lf\n",
            prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
        }
    }
}
void purchaseprod(){
	int quant,i;
    char id[10];
    int z=false;
    count=readFile();
	printf("Sell an Item ");
    printf("\nProduct ID: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<count; i++){
        if (strcmp(id,prod[i].id)==0){
            z=true;
            printf("\nItem found! Containing: \n");
            printf("\nProduct name: %s",prod[i].name);
            printf("\nPrice: %.2lf\n\n",prod[i].price);
            printf("Enter the quantity you want to buy  : ");
            fflush(stdin);
            scanf("%d",&quant);
            if (quant>prod[i].quantity){
                puts("\nInsufficient Quantity\nPlease Restock.\n ");
                break;
            }
            float tempSales = prod[i].sales;
            prod[i].numSold += quant;
            prod[i].quantity -= quant;
            prod[i].sales = quant*(prod[i].price*(prod[i].discount/100.0));
            prod[i].sales += tempSales;
		}
	
	}
    if(z==false)
        printf("Cant find the product id: %s.",id);
	writefile();
}
void deleteprod(){
    count=readFile();
    char id[10]; 
    int i,j;
    int z=false;
    printf("Enter the id that you want to be delete : ");
    fflush(stdin);
    gets(id);
    for(i=0;i<count;i++){
        z=true;
        if(strcmp(prod[i].id,id)==0){
            for( j=i; j<(count-1); j++)
                prod[j]=prod[j+1];
            count--;
        }
    }
    if(z==false)
        printf("Cant find product id: %s .",id);
    writefile();
}
int IDChecker(int i, int j){
    count = readFile();
    printf("Product ID: ");
    fflush(stdin);
    gets(prod[count].id);
    if (strcmp(prod[i].id, prod[j].id) == 0){
        printf("ID number is already taken!");
        return IDChecker(i++, j--);
    }
}
void addProd(){
  	printf("ENTER NEW PRODUCTS\n");
	readFile();
  	if (count>0){
  	    count=readFile();
  		IDChecker(0,count);
	}
	else{
		printf("\nProduct ID Number: ");
		fflush(stdin); 
		gets(prod[count].id);
	}
	printf("Product Name: ");gets(prod[count].name);
	printf("Quantity of the product: ");scanf("%d",&prod[count].quantity);
	printf("Price of the product: ");scanf("%f",&prod[count].price);
	printf("Item Discount: ");scanf("%d",&prod[count].discount);
	++count;
	writefile();
}
int checkID(char id[]){
    int i;
    count = readFile();
    readFile();
    for (i = 0; i < count; i++){
        if (strcmp(id, prod[i].id) != 0)
            fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}
void editProd(){
	char id[10];
    int test;
    int i;
	int choice;
    printf("EDIT A PRODUCT!");
    printf("\nEnter the id of the product that you want to edit: "); // users input for what data will be change
	fflush(stdin);
	gets(id);
	test=checkID(id);
    if (test == 0)
        printf("The id num %s is not found.", id);
    else{
 		readFile();
        for(i=0;i<count;i++){
            if(strcmp(id,prod[i].id)!=0) // if the data is not empty 
                writefile();
            else{
                printf("\n1. Update product ID Number?");
                printf("\n2. Update Name of the product? ");
                printf("\n3. Update Quantitiy of the product?");
                printf("\n4. Update Price of the product?");
                printf("\n5. Update Discount of the product?");
                printf("\nEnter your choice:");
                fflush(stdin);
                scanf("%d", &choice);
                switch (choice){
                    case 1:
                        printf("Enter new ID: ");
                        fflush(stdin);
                        gets(prod[i].id);
                        break;
                    case 2:
                        printf("Enter new Name: ");
                        fflush(stdin);
                        gets(prod[i].name);
                        break;
                    case 3:
                        printf("Enter Quantity: ");
                        scanf("%d",&prod[i].quantity);
                        break;
                    case 4:
                        printf("Enter the new price: ");
                        scanf("%f",&prod[i].price);
                        break;
                    case 5:
                        printf("Enter the new discount of the product: ");
                        scanf("%d",&prod[i].discount);
                    default:
                        printf("Invalid Selection");
                        break;
                }
            writefile();
            }
        }
        f = fopen("Inventory.txt", "r");
        readFile();
        writefile();
    }
    fclose(f);
    printf("RECORD UPDATED");
}
void displayprod(){
	int i;
    count = readFile();
    if (count < 0){
        puts("cannot open file");
        printf(" \t\t\t\t *****  INVENTORY *****\n");
        printf("------------------------------------------------------------------------------------\n");
        printf("S.N.|    NAME     |  PROD ID  |  QUANTITY | PROD SOLD |  PRICE  | DISCOUNT | SALES |\n");
        printf("------------------------------------------------------------------------------------\n");
    }
    for (i=0;i<count;i++){
        printf("%d     %-10s       %-8s     %-5d      %-3d       %-6.2f    %-5d%%    P%.2lf\n",i+1,
        prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
	}
}
int main (){
	int choice;
	count = readFile();
	if(count < 0)
		printf("Cannot locate file\n");
        do{
            printf("\n");
            printf("\t\t\t  ================================\n");
            printf("\t\t\t     PRODUCT INVENTORY PROGRAM\n");
            printf("\t\t\t  ================================");
            printf("\n\nPress:");
            printf("\n 1.) Input new product record.");
            printf("\n 2.) Edit a Product.");
            printf("\n 3.) Delete a Product");
            printf("\n 4.) Display all existing product.");
            printf("\n 5.) Make a purchase.");
            printf("\n 6.) Display the product record with highest sale.");
            printf("\n 7.) Display all product with zero quantity");
            printf("\n 8.) Exit the program.");
            printf("\nChoice?----:-) ");
            scanf("%d", &choice);
            switch(choice){
            case 1 :
                addProd();
                break;
            case 2:
                editProd();
                break;
            case 3:
                deleteprod();
                break;
            case 4:
                displayprod();
                break;
            case 5:
                purchaseprod();
                break;
            case  6:
                dispHsale();
                break;
            case 7:
                disZeroQuant();
                break;
            case 8:
                exit(1);
                break;
            default :
                    printf("Your choice is wrong please try again");
                    break;
            }
        } while(choice!=8);
    printf("Thankyou for using this program");
}
