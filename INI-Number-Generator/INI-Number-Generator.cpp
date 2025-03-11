/* Italian National Insurance Number Generator by DanielIppo & Pall1n contribute: Filippo127*/
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <regex>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>
#include <fstream>
//#include <pqxx/core.hxx>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/result>
using namespace std;

#pragma warning(disable : 4996)

//Line 12 to 41 are the code for embellish the program

string Red = "\x1b[31m";
string Yellow = "\x1b[33m";
string Green = "\x1b[32m";
string Blue = "\x1b[94m";
string Magenta = "\x1b[95m";
string ColorDefault = "\x1b[0m";
string Bold = "\x1b[1m";
string AttributeStringOff = "\x1b[0m";

void sleep3() {
#ifdef _WIN32
	Sleep(3000);
#else
	sleep(3);
#endif
}

void clear() {
#if _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void header() {
	cout << Red << Bold << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@ Italian National Insurance Number Generator @@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << AttributeStringOff << endl << endl;
}

int checkInput(int check, string variable) {
	while (cin.fail()) {
		cin.clear();
		cout << Red << "The number you insert is wrong, Please re-insert it." << AttributeStringOff;
		cin.ignore(1000, '\n');
		sleep3();
		cout << "\33[2K\033[A\33[2K\r" << variable << Green << Bold;
		cin >> check;
		cout << AttributeStringOff;
	}
	return check;
}

class City {
public:
	string CityName;
	string CityCode;

	bool verifyCity(string cityName, string cityProv) {
		try {
			ifstream conf_file("config.json", ifstream::binary);
			if (!conf_file) {
				cerr << "Errore nell'apertura del file!" << endl;
				exit(1);
			}

			Json::Value conf;
			Json::CharReaderBuilder reader;
			string errs;

			if (!Json::parseFromStream(reader, conf_file, &conf, &errs)) {
				cerr << "Errore nel parsing JSON: " << errs << endl;
				exit(1);
			}
            string connectionString = "dbname=" + conf["dbname"].asString() + " user=" + conf["user"].asString() + " password="+ conf["password"].asString() + " host="+ conf["host"].asString() + " port=" + conf["port"].asString();
			pqxx::connection conn(connectionString);
			if (!conn.is_open()) {
				std::cerr << "Connessione fallita!" << std::endl;
			}
			pqxx::work txn(conn);

			pqxx::result res = txn.exec("SELECT denominazione_ita_altra, codice_belfiore FROM gi_comuni_cap WHERE denominazione_ita_altra = '"+ cityName +"' AND sigla_provincia = '"+ cityProv +"'");
			txn.commit();
			if (res.empty()) {
				return false;
			}
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Errore: " << e.what() << std::endl;
		}
	}

	City getCity(string cityName, string cityProv) {
		ifstream conf_file("config.json", ifstream::binary);
		if (!conf_file) {
			cerr << "Errore nell'apertura del file!" << endl;
			exit(1);
		}

		Json::Value conf;
		Json::CharReaderBuilder reader;
		string errs;

		if (!Json::parseFromStream(reader, conf_file, &conf, &errs)) {
			cerr << "Errore nel parsing JSON: " << errs << endl;
			exit(1);
		}
		string connectionString = "dbname=" + conf["dbname"].asString() + " user=" + conf["user"].asString() + " password=" + conf["password"].asString() + " host=" + conf["host"].asString() + " port=" + conf["port"].asString();
		pqxx::connection conn(connectionString);
		if (!conn.is_open()) {
			std::cerr << "Connessione fallita!" << std::endl;
		}
		pqxx::work txn(conn);

		pqxx::result res = txn.exec("SELECT denominazione_ita_altra, codice_belfiore FROM gi_comuni_cap WHERE denominazione_ita_altra = '" + cityName + "' AND sigla_provincia = '" + cityProv + "'");
		City c;
		for (const auto& row : res) {
			c.CityCode = row["codice_belfiore"].as<std::string>();
			c.CityName = row["denominazione_ita_altra"].as<std::string>();
		}
		txn.commit();
		return c;
	}
};

//The class to insert the data of the user
class InsertDate {
public:
	char nameDate[90];
	char surnameDate[90];
	char genderDate[2];
	string birthPlaceDate;
	string birthPlaceProvDate;
	int birthDayDate = 0;
	int birthMonthDate = 0;
	int birthYearDate = 0;
	string birthDate;
	City city;

	char verifyName(char nameDate[]) {
		for (int i = 0; i < strlen(nameDate); i++) {
			if (nameDate[i] >= 'A' && nameDate[i] <= 'Z') {
				continue;
			}
			else if (nameDate[i] >= 'a' && nameDate[i] <= 'z') {
				continue;
			}
			else if (nameDate[i] == ' ') {
				continue;
			}
			else {
				cout << Red << "Invalid name! Please re-insert it." << AttributeStringOff << endl;
				sleep3();
				cout << "\033[A\33[2K\033[A\33[2K\rName: " << Green << Bold;
				// \033[A is the command to move the cursor up, \33[2K is the command to clear the line, \r is the command to return to the beginning of the line
				cout.flush();
				cin >> nameDate;
				cout << AttributeStringOff;
				verifyName(nameDate);
			}
		}
		return nameDate[strlen(nameDate)];
	}

	char verifySurname(char surnameDate[]) {
		for (int i = 0; i < strlen(surnameDate); i++) {
			if (surnameDate[i] >= 'A' && surnameDate[i] <= 'Z') {
				continue;
			}
			else if (surnameDate[i] >= 'a' && surnameDate[i] <= 'z') {
				continue;
			}
			else if (surnameDate[i] == ' ') {
				continue;
			}
			else {
				cout << Red << "Invalid surname! Please re-insert it." << AttributeStringOff << endl;
				sleep3();
				cout << "\033[A\33[2K\033[A\33[2K\rSurname: " << Green << Bold;;
				cout.flush();
				cin >> surnameDate;
				cout << AttributeStringOff;
				verifySurname(surnameDate);
			}
		}
		return surnameDate[strlen(surnameDate)];
	}

	char verifyGender(char gendeDate[]) {
		if (genderDate[0] == 'm' or genderDate[0] == 'M' or genderDate[0] == 'f' or genderDate[0] == 'F') {
		}
		else {
			cout << Red << "Invalid gender! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\rGender [m/f]: " << Green << Bold;;
			cout.flush();
			cin >> genderDate;
			cout << AttributeStringOff;
			verifyGender(genderDate);
		}
		return genderDate[strlen(genderDate)];
	}

	void verifyBirthDate(string& birthDate) {
		regex datePattern(R"(^\d{2}/\d{2}/\d{4}$)");
		if (!regex_match(birthDate, datePattern)) {
			cout << Red << "Invalid birth date! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\rBirth Date [gg/mm/yyyy]: " << Green << Bold;
			cout.flush();
			cin >> birthDate;
			cout << AttributeStringOff;
			verifyBirthDate(birthDate);
		}
		time_t t = time(nullptr);
		tm* today = localtime(&t);

		istringstream ss(birthDate);
		string token;
		vector<int> dateParts;
		while (getline(ss, token, '/')) {
			dateParts.push_back(stoi(token));
		}

		if (dateParts.size() != 3) {
			cout << Red << "Invalid birth date! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\rBirth Date [gg/mm/yyyy]: " << Green << Bold;
			cout.flush();
			cin >> birthDate;
			cout << AttributeStringOff;
			verifyBirthDate(birthDate);
		}

		int day = dateParts[0];
		int month = dateParts[1];
		int year = dateParts[2];

		tm birthTm = {};
		birthTm.tm_mday = day;
		birthTm.tm_mon = month - 1;
		birthTm.tm_year = year - 1900; 

		time_t birthTime = mktime(&birthTm);

		if (birthTime == -1) {
			cout << Red << "Error during converting the birth date! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\rBirth Date [gg/mm/yyyy]: " << Green << Bold;
			cout.flush();
			cin >> birthDate;
			cout << AttributeStringOff;
			verifyBirthDate(birthDate);
		}

		if (birthTime < t) {
			this->birthDayDate = day;
			this->birthMonthDate = month;
			this->birthYearDate = year;
		}
		else {
			cout << Red << "Invalid birth date! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\rBirth Date [gg/mm/yyyy]: " << Green << Bold;
			cout.flush();
			cin >> birthDate;
			cout << AttributeStringOff;
			verifyBirthDate(birthDate);
		}
	}

	string verifyBirthPlace(string birthplacedate, string birthplaceprovdate) {
		City _city; 
		transform(birthplaceprovdate.begin(), birthplaceprovdate.end(), birthplaceprovdate.begin(), ::toupper);
		transform(birthplacedate.begin(), birthplacedate.begin()+1, birthplacedate.begin(), ::toupper);
		if (_city.verifyCity(birthplacedate, birthplaceprovdate) == true) {
			this->city = _city.getCity(birthplacedate, birthplaceprovdate);
			return birthplacedate;
		}
		else {
			cout << Red << "Error: Invalid place of birth! Please re-insert it." << AttributeStringOff << endl;
			sleep3();
			cout << "\033[A\33[2K\033[A\33[2K\033[A\33[2K\rBirth Place: " << Green << Bold;
			cout.flush();
			cin >> birthplacedate;
			cout << AttributeStringOff << "Birth Place Province (abbreviation): " << Green << Bold;
			cin >> birthplaceprovdate;
			cout << AttributeStringOff;
			verifyBirthPlace(birthplacedate, birthplaceprovdate);
		}
	}


	void insertDateFunction() {
		cout << "Name: " << Green << Bold;
		cin >> nameDate;
		cout << AttributeStringOff;
		verifyName(nameDate);

		cout << "Surname: " << Green << Bold;
		cin >> surnameDate;
		cout << AttributeStringOff;
		verifySurname(surnameDate);

		cout << "Gender [m/f]: " << Green << Bold;
		cin >> genderDate;
		cout << AttributeStringOff;
		verifyGender(genderDate);

		cout << "Birth date [gg/mm/yyyy]: " << Green << Bold;
		cin >> birthDate;
		cout << AttributeStringOff;
		verifyBirthDate(birthDate);

		cout << AttributeStringOff << "Birth Place: " << Green << Bold;
		cin >> birthPlaceDate;
		cout << AttributeStringOff << "Birth Place Province (abbreviation): " << Green << Bold;
		cin >> birthPlaceProvDate;
		cout << AttributeStringOff;
		verifyBirthPlace(birthPlaceDate, birthPlaceProvDate);
	}

};

//Class to calculate the Italian National Insurance Number
class GeneratorNIN {
public:
	string consonantsSurname = {};
	string consonantsName = {};
	char splittedYears[90] = {};
	char monthChar = {};
	int dayChar;
	string istatCode = {};
	char controllCode = {};
	string NIN;

	unordered_map<char, int> pariValues = {
	{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9},
	{'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19},
	{'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25},
	{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}
	};

	unordered_map<char, int> dispariValues = {
		{'A', 1}, {'B', 0}, {'C', 5}, {'D', 7}, {'E', 9}, {'F', 13}, {'G', 15}, {'H', 17}, {'I', 19}, {'J', 21},
		{'K', 2}, {'L', 4}, {'M', 18}, {'N', 20}, {'O', 11}, {'P', 3}, {'Q', 6}, {'R', 8}, {'S', 12}, {'T', 14},
		{'U', 16}, {'V', 10}, {'W', 22}, {'X', 25}, {'Y', 24}, {'Z', 23},
		{'0', 1}, {'1', 0}, {'2', 5}, {'3', 7}, {'4', 9}, {'5', 13}, {'6', 15}, {'7', 17}, {'8', 19}, {'9', 21}
	};

	char conversionTable[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };


	void separateConsonants(string consonants, string& consonants1) {
		try {
			int counter = 0;
			for (int i = 0; i < consonants.size(); i++) {
				if (consonants[i] == 'a' || consonants[i] == 'A' || consonants[i] == 'e' || consonants[i] == 'E' || consonants[i] == 'i' || consonants[i] == 'I' || consonants[i] == 'o' || consonants[i] == 'O' || consonants[i] == 'u' || consonants[i] == 'U') {
					continue;
				}
				else {
					consonants1.push_back(toupper(consonants[i]));
					counter++;
					if (counter == 3) {
						break;
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Errore: " << e.what() << std::endl;
		}
	}

    void splitYears(const string& birthyear, char birthyearsplitter[]) {
       birthyearsplitter[0] = birthyear[2];
       birthyearsplitter[1] = birthyear[3];
    }

	void getMonthChar(int month) {
		switch (month)
		{
			case 1:
				this->monthChar = 'A';
				break;
			case 2:
				this->monthChar = 'B';
				break;
			case 3:
				this->monthChar = 'C';
				break;
			case 4:
				this->monthChar = 'D';
				break;
			case 5:
				this->monthChar = 'E';
				break;
			case 6:
				this->monthChar = 'H';
				break;
			case 7:
				this->monthChar = 'L';
				break;
			case 8:
				this->monthChar = 'M';
				break;
			case 9:
				this->monthChar = 'P';
				break;
			case 10:
				this->monthChar = 'R';
				break;
			case 11:
				this->monthChar = 'S';
				break;
			case 12:
				this->monthChar = 'T';
				break;
			default:
				break;
		}
	}

    void getDayChar(int day, char gender) {
        if (gender == 'M' || gender == 'm') {
            this->dayChar = day;
        } else if (gender == 'F' || gender == 'f') {
            this->dayChar = day + 40;
        }
    }
	
	void getControllCode(const string& fiscalCode) {
		if (fiscalCode.length() != 15) {
			cerr << "Errore: Il codice fiscale deve avere 15 caratteri." << endl;
			exit(1);
		}

		int sum = 0;
		for (int i = 0; i < 15; i++) {
			char c = fiscalCode[i];
			if (i % 2 == 0) { 
				sum += dispariValues[c];
			}
			else { 
				sum += pariValues[c];
			}
		}

		int remainder = sum % 26;
		this->NIN += conversionTable[remainder];
	}

    bool generatorInsurance(InsertDate insertDate) {
		cout << Red << "Generating your fiscal code..." << AttributeStringOff << endl;
		separateConsonants(insertDate.surnameDate, this->consonantsSurname);
		separateConsonants(insertDate.nameDate, this->consonantsName);
        splitYears(to_string(insertDate.birthYearDate), this->splittedYears);
        getMonthChar(insertDate.birthMonthDate);
        getDayChar(insertDate.birthDayDate, insertDate.genderDate[0]);
		this->istatCode = insertDate.city.CityCode;
		this->NIN = this->consonantsSurname + this->consonantsName + this->splittedYears + this->monthChar + to_string(insertDate.birthDayDate) + this->istatCode;
		getControllCode(this->NIN);
		return true;
    }
};

int main() {
	header();
	InsertDate insertDate;
	cout << Blue << Bold << "Hello I'm your personal Italian National Insurance Number Generator.\nWrite below your data:" << AttributeStringOff << endl << endl;
	insertDate.insertDateFunction();
	clear();
	header();
	GeneratorNIN generator;
	if (generator.generatorInsurance(insertDate)) {
		clear();
		header();
		cout << Blue << "Your fiscal code is: " << Green << Bold << generator.NIN << AttributeStringOff << endl;
		cout << Blue << "Press any key to exit." << AttributeStringOff;
		cin.get();
	}
	return 0;
}