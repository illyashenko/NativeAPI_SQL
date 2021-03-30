#include "IServiceSQL.h"

vector<map<string, string>> ProcessSqlQuery(const wchar_t* CON_STRING, const wchar_t* REQ_STRING, bool& mistake)
{
    setlocale(LC_ALL, "ru-RU");

    SQLHENV handleEnvironment;
    SQLHDBC handleConnection;
    SQLHSTMT handleStatement;
    SQLRETURN return_sql;
    SQLRETURN querty;
    handleStatement = NULL;
    vector<map<string, string>> resultSql;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnvironment);
    SQLSetEnvAttr(handleEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, handleEnvironment, &handleConnection);

    
    return_sql = SQLDriverConnect(handleConnection, NULL, (SQLWCHAR*)CON_STRING, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    switch (return_sql)
    {
    case SQL_SUCCESS:
        mistake = false;
        break;
    case SQL_SUCCESS_WITH_INFO:
        mistake = false;
        break;
    case SQL_INVALID_HANDLE:
        mistake = true;
        break;
    case SQL_ERROR:
        mistake = true;
        break;
    default:
        break;
    }

	SQLAllocHandle(SQL_HANDLE_STMT, handleConnection, &handleStatement);
	querty = SQLExecDirect(handleStatement, (SQLWCHAR*)REQ_STRING, SQL_NTS);

	if (SQL_SUCCESS != querty)
	{
        mistake = true;
	}

	SQLCHAR sqlVersion[SQL_RESULT_LEN];
	SQLWCHAR colName[SQL_RESULT_LEN];
	SQLLEN ptrSqlVersion;
	SQLSMALLINT ptrColumnCount;
	SQLNumResultCols(handleStatement, &ptrColumnCount);
	while (SQLFetch(handleStatement) == SQL_SUCCESS)
	{

        map<string, string> resultMap;
		for (SQLSMALLINT i = 1; i <= ptrColumnCount; i++)
		{
			SQLDescribeCol(handleStatement, i, colName, sizeof(colName), 0, 0, 0, 0, 0);
			SQLGetData(handleStatement, i, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);

			wstring columName(colName);
			string col_sql(columName.begin(), columName.end());
			string s_sql(reinterpret_cast<char*>(sqlVersion));
			resultMap.insert(pair<string, string>(col_sql, s_sql));
		}

		resultSql.push_back(resultMap);
	}

	return resultSql;
}

string GetJsonString(vector<map<string, string>>& vectorResponse)
{
	string str_array;
	int a = 1;
	str_array += '[';
	for (map<string, string> it_vector : vectorResponse)
	{
		string struct_map;
		int s = 1;
		struct_map += '{';
		for (const auto& it : it_vector)
		{
			struct_map += '"' + it.first + '"' + " : " + '"' + it.second + '"';
			struct_map += (it_vector.size() != s) ? "," : "";
			s++;
		}
		struct_map += '}';
		str_array += struct_map;
		str_array += (vectorResponse.size() != a) ? "," : "";
		a++;
	}
	str_array += ']';
	return str_array;
}
