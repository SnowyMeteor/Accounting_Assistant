#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <time.h> 
using namespace std;

void Create(void);	//�[�J 
void Insert(void);	//���J 
void Delete(void);	//�R�� 
void Read(void);	//��� 
void Update(void);	//��s 
void Load(void);	//Ū���ɮ� 
void Save_new(void);	//�t�s�ɮ�
void Save_org(void);	//�x�s�ɮ� 
void org_account(void);	//�±b������ 
void new_account(void);	//�s�b������ 
void Default(void);	//�D���� 
int set = 0;		//�쵲��C�ƶq 

struct Account //�`�I����� 
{
	char item[20];	//���� 
	int spend;		//���B 
	struct Account *next;	
};

struct Account  *current, *ptr, *prev;	//current�O��e�ҰѷӪ��쵲�B�Aptr�O�쵲������ơAprev�O���V��e�ҰѷӪ��e�@���쵲�B
struct Account *head = (struct Account *)malloc(sizeof(struct Account));	//��head�[�J��C�e��(�ҥ�4-3 �[�J�ʧ@1-1) 

int main() 
{
	char first_choose;	
	char second_choose;
	while(1)
	{
		Default();
		cin >> first_choose;
		if(first_choose =='1') //�s�b�� 
		{
			while(1)	//��ܥ\��
			{	 
				cout << endl;
				new_account();
				cin >> second_choose; 
				switch(second_choose) 
				{
					case '1':
						Create();
						set++;	//�C�W�[�@���N���쵲��C�[�@ 
						break;
					case '2':
						Read();
						break;
					case '3':
						Update();
						break;
					case '4':
						Delete();
						set--;	//�C�R���@���N���쵲��C��@ 
						break;
					case '5':
						Save_new();
						break;
					case '6':
						cout << "�A���@�U�H�����{��!" << endl;
						system("PAUSE");
						return 0;
						break;
					default:
						cout << "�п�J���T���s��!" << endl; 
						break;
				}
			}	
		}
		else if(first_choose =='2')	//�±b�� 
		{
			Load();
			while(1)	//��ܥ\��
			{	 
				cout << endl;
				org_account();
				cin >> second_choose; 
				switch(second_choose) 
				{
					case '1':
						Create();
						set++;	//�C�W�[�@���N���쵲��C�[�@  
						break;
					case '2':
						Read();
						break;
					case '3':
						Update();
						break;
					case '4':
						Delete();
						set--;	//�C�R���@���N���쵲��C��@ 
						break;
					case '5':
						Save_org();
						break;
					case '6':
						cout << "�A���@�U�H�����{��!" << endl;
						system("PAUSE");
						return 0;
						break;
					default:
						cout << "�п�J���T���s��!" << endl; 
						break;
				}
			}
		}
		else if(first_choose =='3')	//���� 
		{
			cout << "�A���@�U�H�����{��!" <<endl;
			system("PAUSE");
			return 0;
		}
		else
		{
			cout << "�п�J���T���s��!" << endl;
			cout << "------------------------" << endl;	
		}	
	}
}

void Create(void) //�s�W���� 
{	
	int spend;
	cout << "�s�W���ؤ�..." << endl;
	ptr = (struct Account *) malloc(sizeof(struct Account));
	//��J���ؤΪ��B 
	cout << "����:"; 
	cin >> ptr->item;
	cout << "���B:";
	cin >> ptr->spend;
	current = (struct Account *) malloc(sizeof(struct Account)); 
	prev = head;
	current = head->next;
	
	while (current != NULL && (current->spend > ptr->spend)) 
	{
		prev = current; 			//�����쥻����e�`�I��m
		current = current->next; 	//�̷ӷ�e�`�I�����U�@�Ӹ`�I 
	}	
	ptr->next = current;	//ptr��next���Vcurrent����}
	prev->next = ptr;		//prev��next���Vptr����}
	cout << "------------------------" << endl;	
}

void Read()	//��ܶ��� 
{
	int total=0;
	prev = head;
	current = head->next;
	cout << "Ū�����ؤ�..."<< endl;
	if(set == 0)
	{
		cout << "�b�����L���󶵥�!" << endl;
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
		cout << "�֭p���O�`�B:\t" << total << endl; 
	}
	cout << "------------------------" << endl; 		
}

void Update()	//��s���� 
{
	char Update_item[20],Update_spend[10];
	cout << "��s���ؤ�..."<< endl;
	if(head->next == NULL)
	{
		cout << "�L���󶵥ظ��!"<< endl; 
	}
	else
	{
		cout << "�п�J���ק諸���ئW��:";
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
			cout << "����:" << current->item << endl;
			cout << "���B:" << current->spend << endl;
			cout << "�п�J���ק諸���B:";
			cin >> Update_spend;
			prev->next = current->next;
			delete current;
			
			//���s�Ƨ�
			ptr = (struct Account*)malloc(sizeof(struct Account));	//�Nptr��J��C���e�� 
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
			cout << Update_item << "���ؤw��s!" << endl; 
		}
		else
		{
			cout << Update_item << "�䤣��Ӷ���!" << endl; 
		}
	}
}

void Delete() //�R������ 
{
	char del_item[20];
	cout << "�R�����ؤ�..."<< endl;
	if(head->next==NULL)
	{
		cout << "�L���󶵥ظ��" << endl; 
	} 
	else
	{
		cout << "�п�J���R��������:";
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
			cout << del_item << "���ؤw�R��!" << endl; 
		}
		else
		{
			cout << del_item << "�䤣��Ӷ���!" << endl; 
		}
	}
	cout << "------------------------" << endl;	
}

void Save_new()	//�t�s�ɮ� 
{
	prev = head; 
	current = prev->next;
	char file_name[16];
	cout << "�x�s���s�b����..." << endl;
	cout << "�ɮצW��(�аO�o�[�W.txt):";
	cin >> file_name;
	fstream bool_file;
	bool_file.open(file_name,ios::in); //�P�_�O�_�s�b�Ӥ�� 
	
	if(!bool_file) //�ɮפ��s�b 
	{
		fstream file;
		file.open(file_name,ios::out); //True(�g�J) 
		
		for(int i = 0; i < set; i++)	//set���`�ƨӧP�_�s�������� 
		{
			file << current->item << "\t";
			file << current->spend << endl;
			current = current->next;	
		}	
		file.close();	//�����ɮ� 
		cout << file_name << "�b���w�إ�!" << endl;
	}	
	else	
	{
		cout <<"�b���w�s�b�A�Ыإ߷s�b���ζ}���±b��!"<< endl; //False(�w���ɮ�) 
	}
	cout << "------------------------" << endl;	
}

void Save_org()	//�x�s�ɮ� 
{
	prev = head; 
	current = prev->next;
	char file_name[16];
	cout << "�x�s��e���e��..." << endl;
	cout << "�ɮצW��(�аO�o�[�W.txt):";
	cin >> file_name;

	fstream file;
	file.open(file_name,ios::out); //�N��e���G�мg�A�Y�ɮפ��w����ơA�|����clear 
		
	for(int i = 0; i < set; i++)	
	{
		file << current->item << "\t";
		file << current->spend << endl;
		current = current->next;	
	}	
		file.close();
		cout << file_name << "�b���w�x�s!" << endl;	
		cout << "------------------------" << endl;	
}

void Load()	//Ū���ɮ� 
{
	cout << "Ū�����v�b����..." << endl;
	char file_name[16];
	cout << "�ɮצW��(�аO�o�[�W.txt)�G";
	cin >> file_name;
	prev = head;
	char item[20];
	int spend = 0;
	
		//C�y�����ɮ׬y(�ѦҺ����d��)(stdio.h) 
		FILE *fp; 	//�ŧi�ɮ׫���fp
		if ((fp = fopen(file_name, "r")) != NULL) 	//�P�_���L���ɮסA�Y���N�s��file_name "r"=�iŪ(�奻�Ҧ�) 
		{
			while (fscanf(fp, "%s %d\n", item, &spend) != EOF)	//fscanf���wŪ�����e�����O %s��X�r��B%d��X��ơBEOF�ɮ׵��� 
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
			cout << file_name << "�wŪ�������A�i�}�l�i������ާ@!" << endl ; 
			fclose(fp);
		}
		else
		{
			cout << file_name << "�A�䤣�즹�b��!" << endl;  
			cout << "�t�αN���z�Ыؤ@�ӷs�b��!" << endl; 
		}			
	cout << "------------------------" << endl;
}

void Default()	//�D���� 
{
	cout << "�ϥΪ̱z�n�A�w��ϥΡu�b�� Assistant�v!" << endl;
	cout << "1.�إ߷s�b��" << endl;
	cout << "2.�}���±b��" << endl;
	cout << "3.�����{��" << endl;
	cout << "------------------------" << endl;
	cout << "�п�J�����檺�ʧ@�s��(1-3):";
}

void org_account()	//�±b������ 
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "�褸%Y�~%m��%d�� \n%p %H:%M(%A)", localtime(&t));	//�ɶ����(time.h) 
	cout << tmp << endl;
	cout << "�Ш̤U��Ʀr��i��ާ@!" << endl;
	cout << "1.�s�W�@�Ӷ���" << endl;	//Create
	cout << "2.Ū���Ҧ�����" << endl;	//Read
	cout << "3.��s���ظ��" << endl;	//Update
	cout << "4.�R�����w����" << endl;	//Delete
	cout << "5.�x�s��e���e" << endl;	//Save_org 
	cout << "6.�������ε{��" << endl; 	//Exit
	cout << "------------------------" << endl;
	cout << "�п�J�����檺�ʧ@�s��(1-6):";
}

void new_account()	//�s�b������ 
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "�褸%Y�~%m��%d�� \n%p %H:%M(%A)", localtime(&t));	//�ɶ����(time.h) 
	cout << tmp << endl;
	cout << "�Ш̤U��Ʀr��i��ާ@!" << endl;
	cout << "1.�s�W�@�Ӷ���" << endl;	//Create
	cout << "2.Ū���Ҧ�����" << endl;	//Read
	cout << "3.��s���ظ��" << endl;	//Update
	cout << "4.�R�����w����" << endl;	//Delete
	cout << "5.�x�s���s�b��" << endl;	//Save_new
	cout << "6.�������ε{��" << endl; 	//Exit
	cout << "------------------------" << endl;
	cout << "�п�J�����檺�ʧ@�s��(1-6):";
}
