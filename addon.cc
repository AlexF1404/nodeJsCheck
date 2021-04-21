#include <node.h>
#include <string>
#include <assert.h>
#include <windows.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <lm.h>
#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <string>
#include <atlstr.h>
using namespace std;
namespace addon {

  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Number;
  using v8::Object;
  using v8::String;
  using v8::Value;
  using v8::Boolean;

  void Method(const FunctionCallbackInfo<v8::Value>& args) {

    v8::Isolate* isolate = args.GetIsolate();
    v8::Local<v8::String> nameUserV;
    v8::Local<v8::Boolean> UserAns;
    nameUserV = args[0].As<v8::String>();
    char* charFileName = new char[8192];
    (*nameUserV)->WriteUtf8(isolate, charFileName);
    std::string nameUser;
    nameUser.assign(charFileName);
    bool it(false);
    setlocale(LC_ALL, "Rus");
    DWORD dwlevel = 0;
    DWORD dwfilter = 0;
    USER_INFO_0* theEntries = new USER_INFO_0[20];
    DWORD dwprefmaxlen = 512;
    DWORD dwentriesread;
    DWORD dwtotalentries;
    NET_API_STATUS result;
    result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);    
    for (int i = 0; i < dwentriesread; i++)
    {
        std::wstring s(theEntries[i].usri0_name);
        string myVarS = string(s.begin(), s.end());
        std::transform(myVarS.begin(), myVarS.end(), myVarS.begin(), tolower);
        std::transform(nameUser.begin(), nameUser.end(), nameUser.begin(), tolower);
        if (nameUser == myVarS)
        {
            it = true;
        }
    }
    NetApiBufferFree (theEntries);
    args.GetReturnValue().Set(it);
  }

  void Initialize(v8::Local<v8::Object> exports) {
      NODE_SET_METHOD(exports, "addon", Method);
  }
  NODE_MODULE(addon, Initialize)

}
// namespace demo
