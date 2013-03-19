/* Copyright (c) 2003, 2005 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA */

#include <common.h>

using namespace std;

#define NAME_LEN 50
#define PHONE_LEN 10
#define SALES_PERSON_LEN 10
#define STATUS_LEN 6
#define SQL_MAXIMUM_MESSAGE_LENGTH 200

SQLHSTMT    hstmt;
SQLHDESC    hdesc;

SQLSMALLINT RecNumber;
SQLCHAR     szSalesPerson[SALES_PERSON_LEN];

SQLCHAR     Sqlstate[5], Msg[SQL_MAXIMUM_MESSAGE_LENGTH];
SQLINTEGER  NativeError;
SQLRETURN retcode, SQLSTATEs;

SQLINTEGER   ValuePtr1;
SQLCHAR      ValuePtr2;
SQLSMALLINT  ValuePtr3;

SQLSMALLINT i, MsgLen;

void SQLSetDescFieldTest_DisplayError(SQLSMALLINT HandleType, SQLHDESC InputHandle);

int SQLSetDescFieldTest()
{

  /* hstmt */
  // SQLPrepare a statement to select rows from the ORDERS Table. We can create the table and inside rows in 
  // NDB by another program TestDirectSQL. In this test program(SQLGetDescRecTest),we only have three rows in
  // table ORDERS

/* Prepare the SQL statement with parameter markers. */
retcode = SQLPrepare(hstmt, (SQLCHAR *)"SELECT ORDERID, CUSTID, OPENDATE, SALESPERSON, STATUS FROM ORDERS)", SQL_NTS);

/* SELECT OrderID, CustID, OpenDate, SalesPerson from Table ORDERS */

if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
  retcode = SQLExecute(hstmt);
if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

  /* If FI(FieldIdentifer) is not one of the code values in Table 20 */
retcode = SQLSetDescField(hdesc, 1, 9999, &ValuePtr1, 128);
if  (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
   SQLSetDescFieldTest_DisplayError(SQL_HANDLE_DESC, hdesc);


  /* RecoderNumber is less than 1 and the value of the Type column in the Table is ITEM */
retcode = SQLSetDescField(hdesc, -1, SQL_DESC_LENGTH, &ValuePtr1, 128);
if  (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
   SQLSetDescFieldTest_DisplayError(SQL_HANDLE_DESC, hdesc);


}

}

  return 0;

 }


void SQLSetDescFieldTest_DisplayError(SQLSMALLINT HandleType, SQLHDESC InputHandle)
{
     i = 1;
     while ((SQLSTATEs = SQLGetDiagRec(HandleType, InputHandle, i, 
             Sqlstate, &NativeError, Msg, sizeof(Msg), 
             &MsgLen)) != SQL_NO_DATA)                   {

     ndbout << "the HandleType is:" << HandleType << endl;
     ndbout << "the InputHandle is :" << InputHandle << endl;
     ndbout << "the output state is:" << (char *)Sqlstate << endl; 

     i ++;
                                                         }

}



