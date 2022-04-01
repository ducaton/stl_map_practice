#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void MapSearch (map <string,string> &dict) {
	string word;
	cout<<"\nКакое слово желаете перевести?"<<endl;
	cin.clear();
	getline(cin,word);
	cout<<endl;
	if (dict[word]=="") {
		cout<<"Слово отсутствует в словаре"<<endl;
		dict.erase(word);
		return;
	}
	cout<<word<<" - "<<dict[word]<<endl;
}
void MapAdd(map <string,string> &dict, bool lang) {
	cout<<"\nК какому слову желаете добавить перевод?"<<endl;
	string word, translation;
	cin.clear();
	getline(cin,word);
	char w=word.at(0);
	if ((int(w)<0 && !lang) || (int(w)>0 && lang)) {
		cout<<"\nНеверный язык"<<endl;
		return;
	}
	if (dict[word]!="") {
		cout<<"\nУ этого слова уже есть перевод. Желаете дополнить его? [y/n] ";
		char c;
		cin>>c;
		cin.ignore(500,'\n');
		if (c!='y') return;
		getline(cin,translation);
		w=translation.at(0);
		if ((int(w)<0 && lang) || (int(w)>0 && !lang)) {
		    cout<<"\nНеверный язык"<<endl;
		    return;
        }
		dict[word].append(", ");
		dict[word].append(translation);
		cout<<"\nПеревод дополнен"<<endl;
		return;
	}
	cout<<"\nВведите ваш перевод (0 - отмена)"<<endl;
	getline(cin,translation);
	w=translation.at(0);
	if (translation=="0") {
		dict.erase(word);
		return;
	}
	if ((int(w)<0 && lang) || (int(w)>0 && !lang)) {
		cout<<"\nНеверный язык"<<endl;
		dict.erase(word);
		return;
	}
	dict[word].append(translation);
	cout<<"\nСлово добавлено в словарь"<<endl;
}
void MapDel(map <string,string> &dict) {
	string word;
	cout<<"\nКакое слово желаете удалить?"<<endl;
	cin.clear();
	getline(cin,word);
	cout<<endl;
	if (dict[word]=="") {
		cout<<"Слово отсутствует в словаре"<<endl;
		dict.erase(word);
		return;
	}
	dict.erase(word);
	cout<<"Слово успешно удалено"<<endl;
}
void MapReadFile (map <string,string> &dict, string filename, bool lang) {
	string a,b;
	ifstream file(filename.c_str());
	if (!file.is_open()) {
		cout<<"\nФайл словаря не найден"<<endl;
		return;
	}
	char w=file.peek();
	if ((int(w)<0 && !lang) || (int(w)>0 && lang)) {
		cout<<"\nУказан словарь другого языка, чтение невозможно"<<endl;
		file.close();
		return;
	}
	dict.clear();
	while (file.eof()==false){
		getline(file,a);
		getline(file,b);
		if (a=="") break;
		dict.insert(pair<string,string>(a,b));
	}
	file.close();
	cout<<"\nФайл успешно открыт"<<endl;
}
void MapWriteFile(map <string,string> &dict, string filename) {
	ifstream file(filename.c_str());
	if (file.is_open()) {
		file.close();
		cout<<"\nВы уверены, в том что хотите перезаписать этот файл? [y/n] ";
		char c;
		cin>>c;
		cin.ignore(500,'\n');
		if (c!='y') {
			file.close();
			return;
		}
	}
	ofstream file2(filename.c_str(), ofstream::trunc);
	file2.close();
	ofstream file3(filename.c_str());
	for (map<string,string>::iterator i=dict.begin(); i!=dict.end(); i++) {
		file3<<i->first<<endl<<i->second<<endl;
	}
	file3.close();
	cout<<"\nФайл успешно сохранен"<<endl;
}
void MapPrint (map <string,string> &dict) {	
	cout<<endl;
	if (dict.empty()==true) {
		cout<<"Словарь пуст"<<endl;
		return;
	}
	for (map<string,string>::iterator i=dict.begin(); i!=dict.end(); i++) {
		cout<<i->first<<" - "<<i->second<<endl;
	}
}

void MapMain (map <string,string> &dict, bool lang) {
	char choice;
	string fname;
	if (lang == false) fname = "EnRu.txt";
	else fname = "RuEn.txt";
	MapReadFile(dict,fname,lang);
	while(1) {
		if (lang == false) cout<<"\nАНГЛО-РУССКИЙ СЛОВАРЬ"<<endl;
		else cout<<"\nРУССКО-АНГЛИЙСКИЙ СЛОВАРЬ"<<endl;
		cout<<"1.Показать перевод слова\n2.Добавить перевод слова\n3.Удалить слово\n4.Открыть файл\n5.Сохранить\n6.Сохранить как...\n7.Вывести весь словарь\n0.Выход из словаря"<<endl;
		cin>>choice;
		cin.ignore(500,'\n');
		switch (choice) {
			case '0':
				return;
			case '1':
				MapSearch(dict);
				break;
			case '2':
				MapAdd(dict,lang);
				break;
			case '3':
				MapDel(dict);
				break;
			case '4':
				cout<<"\nКакой файл желаете открыть?"<<endl;
				cin.clear();
				getline(cin,fname);
				MapReadFile(dict,fname,lang);
				break;
			case '5':
				MapWriteFile(dict,fname);
				break;
			case '6':
				cout<<"\nВведите название файла для сохранения"<<endl;
				cin.clear();
				getline(cin,fname);
				MapWriteFile(dict,fname);
				break;
			case '7':
				MapPrint(dict);
				break;
			default:
				cout<<"\nКоманда не найдена"<<endl;
				break;
		}
	}
}

int main() {
	map <string,string, less<string> > EnRu;
	map <string,string, less<string> > RuEn;
	char choice;
	while(1) {
		cout<<"\nВыберите режим работы:\n1.Англо-русский словарь\n2.Русско-английский словарь\n0.Выход из программы"<<endl;
		cin>>choice;
		cin.ignore(500,'\n');
		switch (choice) {
			case '0':
				return 0;
			case '1':
				MapMain(EnRu, false);
				break;
			case '2':
				MapMain(RuEn, true);
				break;
			default:
				cout<<"\nКоманда не найдена"<<endl;
				break;
		}
	}
}
