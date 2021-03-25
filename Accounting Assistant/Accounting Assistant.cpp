#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <time.h> 
using namespace std;

void Create(void);	//加入 
void Insert(void);	//插入 
void Delete(void);	//刪除 
void Read(void);	//顯示 
void Update(void);	//更新 
void Load(void);	//讀取檔案 
void Save_new(void);	//另存檔案
void Save_org(void);	//儲存檔案 
void org_account(void);	//舊帳本頁面 
void new_account(void);	//新帳本頁面 
void Default(void);	//主頁面 
int set = 0;		//鏈結串列數量 

struct Account //節點的資料 
{
	char item[20];	//項目 
	int spend;		//金額 
	struct Account *next;	
};

struct Account  *current, *ptr, *prev;	//current是當前所參照的鏈結處，ptr是鏈結中的資料，prev是指向當前所參照的前一個鏈結處
struct Account *head = (struct Account *)malloc(sizeof(struct Account));	//把head加入串列前端(課本4-3 加入動作1-1) 

int main() 
{
	char first_choose;	
	char second_choose;
	while(1)
	{
		Default();
		cin >> first_choose;
		if(first_choose =='1') //新帳本 
		{
			while(1)	//選擇功能
			{	 
				cout << endl;
				new_account();
				cin >> second_choose; 
				switch(second_choose) 
				{
					case '1':
						Create();
						set++;	//每增加一筆就讓鏈結串列加一 
						break;
					case '2':
						Read();
						break;
					case '3':
						Update();
						break;
					case '4':
						Delete();
						set--;	//每刪除一筆就讓鏈結串列減一 
						break;
					case '5':
						Save_new();
						break;
					case '6':
						cout << "再按一下以關閉程式!" << endl;
						system("PAUSE");
						return 0;
						break;
					default:
						cout << "請輸入正確的編號!" << endl; 
						break;
				}
			}	
		}
		else if(first_choose =='2')	//舊帳本 
		{
			Load();
			while(1)	//選擇功能
			{	 
				cout << endl;
				org_account();
				cin >> second_choose; 
				switch(second_choose) 
				{
					case '1':
						Create();
						set++;	//每增加一筆就讓鏈結串列加一  
						break;
					case '2':
						Read();
						break;
					case '3':
						Update();
						break;
					case '4':
						Delete();
						set--;	//每刪除一筆就讓鏈結串列減一 
						break;
					case '5':
						Save_org();
						break;
					case '6':
						cout << "再按一下以關閉程式!" << endl;
						system("PAUSE");
						return 0;
						break;
					default:
						cout << "請輸入正確的編號!" << endl; 
						break;
				}
			}
		}
		else if(first_choose =='3')	//結束 
		{
			cout << "再按一下以關閉程式!" <<endl;
			system("PAUSE");
			return 0;
		}
		else
		{
			cout << "請輸入正確的編號!" << endl;
			cout << "------------------------" << endl;	
		}	
	}
}

void Create(void) //新增項目 
{	
	int spend;
	cout << "新增項目中..." << endl;
	ptr = (struct Account *) malloc(sizeof(struct Account));
	//輸入項目及金額 
	cout << "項目:"; 
	cin >> ptr->item;
	cout << "金額:";
	cin >> ptr->spend;
	current = (struct Account *) malloc(sizeof(struct Account)); 
	prev = head;
	current = head->next;
	
	while (current != NULL && (current->spend > ptr->spend)) 
	{
		prev = current; 			//紀錄原本的當前節點位置
		current = current->next; 	//依照當前節點往後找下一個節點 
	}	
	ptr->next = current;	//ptr的next指向current的位址
	prev->next = ptr;		//prev的next指向ptr的位址
	cout << "------------------------" << endl;	
}

void Read()	//顯示項目 
{
	int total=0;
	prev = head;
	current = head->next;
	cout << "讀取項目中..."<< endl;
	if(set == 0)
	{
		cout << "帳本內無任何項目!" << endl;
	}
	else
	{
		for(int i = 0 ; i < set; i++)
		{
			cout << current->item << "\t" << current->spend << endl;
			total += current->spend;
			current = current->next;
		}
		cout << endl;
		cout << "累計消費總額:\t" << total << endl; 
	}
	cout << "------------------------" << endl; 		
}

void Update()	//更新項目 
{
	char Update_item[20],Update_spend[10];
	cout << "更新項目中..."<< endl;
	if(head->next == NULL)
	{
		cout << "無任何項目資料!"<< endl; 
	}
	else
	{
		cout << "請輸入欲修改的項目名稱:";
		cin >> Update_item;
		prev = head;
		current = head->next;
		while((current != NULL) && (strcmp(current->item,Update_item)!=0))
		{
			prev = current;
			current = current->next;
		}
		if(current != NULL)
		{
			cout << "項目:" << current->item << endl;
			cout << "金額:" << current->spend << endl;
			cout << "請輸入欲修改的金額:";
			cin >> Update_spend;
			prev->next = current->next;
			delete current;
			
			//重新排序
			ptr = (struct Account*)malloc(sizeof(struct Account));	//將ptr放入串列的前端 
			strcpy(ptr->item,Update_item);
			ptr->spend = atoi(Update_spend);
			ptr->next = NULL;
			prev = head;
			current = head->next;
			while((current != NULL) && (current->spend > ptr->spend))
			{
				prev = current;
				current = current->next;
			}
			ptr->next = current;
			prev->next = ptr;
			cout << Update_item << "項目已更新!" << endl; 
		}
		else
		{
			cout << Update_item << "找不到該項目!" << endl; 
		}
	}
}

void Delete() //刪除項目 
{
	char del_item[20];
	cout << "刪除項目中..."<< endl;
	if(head->next==NULL)
	{
		cout << "無任何項目資料" << endl; 
	} 
	else
	{
		cout << "請輸入欲刪除的項目:";
		cin >> del_item;
		prev = head;
		current = head->next;
		while((current != NULL)&&(strcmp(current->item,del_item)!=0))  
		{
			prev = current;
			current = current->next;
		}
		if(current != NULL)
		{
			prev->next = current->next;
			delete current;
			cout << del_item << "項目已刪除!" << endl; 
		}
		else
		{
			cout << del_item << "找不到該項目!" << endl; 
		}
	}
	cout << "------------------------" << endl;	
}

void Save_new()	//另存檔案 
{
	prev = head; 
	current = prev->next;
	char file_name[16];
	cout << "儲存為新帳本中..." << endl;
	cout << "檔案名稱(請記得加上.txt):";
	cin >> file_name;
	fstream bool_file;
	bool_file.open(file_name,ios::in); //判斷是否存在該文件 
	
	if(!bool_file) //檔案不存在 
	{
		fstream file;
		file.open(file_name,ios::out); //True(寫入) 
		
		for(int i = 0; i < set; i++)	//set的總數來判斷存取的長度 
		{
			file << current->item << "\t";
			file << current->spend << endl;
			current = current->next;	
		}	
		file.close();	//關閉檔案 
		cout << file_name << "帳本已建立!" << endl;
	}	
	else	
	{
		cout <<"帳本已存在，請建立新帳本或開啟舊帳本!"<< endl; //False(已有檔案) 
	}
	cout << "------------------------" << endl;	
}

void Save_org()	//儲存檔案 
{
	prev = head; 
	current = prev->next;
	char file_name[16];
	cout << "儲存當前內容中..." << endl;
	cout << "檔案名稱(請記得加上.txt):";
	cin >> file_name;

	fstream file;
	file.open(file_name,ios::out); //將當前結果覆寫，若檔案內已有資料，會直接clear 
		
	for(int i = 0; i < set; i++)	
	{
		file << current->item << "\t";
		file << current->spend << endl;
		current = current->next;	
	}	
		file.close();
		cout << file_name << "帳本已儲存!" << endl;	
		cout << "------------------------" << endl;	
}

void Load()	//讀取檔案 
{
	cout << "讀取歷史帳本中..." << endl;
	char file_name[16];
	cout << "檔案名稱(請記得加上.txt)：";
	cin >> file_name;
	prev = head;
	char item[20];
	int spend = 0;
	
		//C語言的檔案流(參考網路範例)(stdio.h) 
		FILE *fp; 	//宣告檔案指標fp
		if ((fp = fopen(file_name, "r")) != NULL) 	//判斷有無該檔案，若有就連結file_name "r"=可讀(文本模式) 
		{
			while (fscanf(fp, "%s %d\n", item, &spend) != EOF)	//fscanf指定讀取內容的類別 %s輸出字串、%d輸出整數、EOF檔案結尾 
			{
				ptr = (struct Account*)malloc(sizeof(struct Account));
				strcpy(ptr->item, item);
				ptr->spend = spend;
				if (set == 0) 
				{
					head->next = ptr;
					current = ptr;
				}
				else 
				{
					current->next = ptr;
					current = ptr;
				}
				set++; 
			}
			cout << file_name << "已讀取完成，可開始進行相關操作!" << endl ; 
			fclose(fp);
		}
		else
		{
			cout << file_name << "，找不到此帳本!" << endl;  
			cout << "系統將為您創建一個新帳本!" << endl; 
		}			
	cout << "------------------------" << endl;
}

void Default()	//主頁面 
{
	cout << "使用者您好，歡迎使用「帳務 Assistant」!" << endl;
	cout << "1.建立新帳本" << endl;
	cout << "2.開啟舊帳本" << endl;
	cout << "3.關閉程式" << endl;
	cout << "------------------------" << endl;
	cout << "請輸入欲執行的動作編號(1-3):";
}

void org_account()	//舊帳本頁面 
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "西元%Y年%m月%d日 \n%p %H:%M(%A)", localtime(&t));	//時間顯示(time.h) 
	cout << tmp << endl;
	cout << "請依下方數字鍵進行操作!" << endl;
	cout << "1.新增一個項目" << endl;	//Create
	cout << "2.讀取所有項目" << endl;	//Read
	cout << "3.更新項目資料" << endl;	//Update
	cout << "4.刪除指定項目" << endl;	//Delete
	cout << "5.儲存當前內容" << endl;	//Save_org 
	cout << "6.關閉應用程式" << endl; 	//Exit
	cout << "------------------------" << endl;
	cout << "請輸入欲執行的動作編號(1-6):";
}

void new_account()	//新帳本頁面 
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "西元%Y年%m月%d日 \n%p %H:%M(%A)", localtime(&t));	//時間顯示(time.h) 
	cout << tmp << endl;
	cout << "請依下方數字鍵進行操作!" << endl;
	cout << "1.新增一個項目" << endl;	//Create
	cout << "2.讀取所有項目" << endl;	//Read
	cout << "3.更新項目資料" << endl;	//Update
	cout << "4.刪除指定項目" << endl;	//Delete
	cout << "5.儲存為新帳本" << endl;	//Save_new
	cout << "6.關閉應用程式" << endl; 	//Exit
	cout << "------------------------" << endl;
	cout << "請輸入欲執行的動作編號(1-6):";
}
