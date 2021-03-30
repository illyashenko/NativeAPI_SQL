#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlext.h>
#include <string>
#include <winnt.h>
#include <vector>
#include <map>

#define SQL_RESULT_LEN 240
using namespace std;

vector<map<string, string>> ProcessSqlQuery(const wchar_t* CON_STRING, const wchar_t* REQ_STRING, bool& mistake);

string GetJsonString(vector<map<string, string>>& vectorResponse);




/*
    **************************** SQL connections string ODBC ***********************************
     const wchar_t* STR_SQL = L"DRIVER={SQL Server};PWD=admin;UID=admin;SERVER=127.1.1.0";

     *********************************** SQL request *******************************************
     const wchar_t* STR_REQUEST = L"SELECT \
                                        client1C.OneSID, \
                                        client.Company_name, \
                                        addr.Address, \
                                        addr.PostCode, \
                                        jc.CityName \
                                    FROM [ClientsVs1C] client1C \
                                    WHERE client.INN in('5032212790/503201001', '7714037390/997150001')";
   *********************************************************************************************
*/
