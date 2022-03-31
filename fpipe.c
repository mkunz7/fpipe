void sub_401000(char *Format, ...)
{
  char Dest; // [esp+0h] [ebp-400h]
  va_list Args; // [esp+40Ch] [ebp+Ch]

  va_start(Args, Format);
  vsprintf(&Dest, Format, Args);
  fprintf(&iob[2], &Dest);
  OutputDebugStringA(&Dest);
}

void sub_401047(char *Format, ...)
{
  char Dest; // [esp+0h] [ebp-400h]
  va_list va; // [esp+40Ch] [ebp+Ch]

  va_start(va, Format);
  if ( dword_404C58 )
  {
    vsprintf(&Dest, Format, va);
    printf(&Dest);
    OutputDebugStringA(&Dest);
  }
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  HMODULE v3; // eax
  BOOL i; // eax
  struct tagMSG Msg; // [esp+8h] [ebp-1Ch]

  v3 = GetModuleHandleA(0);
  if ( sub_4010FE(v3) && sub_401250(argc) && sub_4015C7() )
  {
    for ( i = GetMessageA(&Msg, 0, 0, 0); i > 0; i = GetMessageA(&Msg, 0, 0, 0) )
    {
      TranslateMessage(&Msg);
      DispatchMessageA(&Msg);
    }
  }
  sub_4011FD();
  return 0;
}

signed int __cdecl sub_4010FE(HINSTANCE hInstance)
{
  struct WSAData WSAData; // [esp+Ch] [ebp-1B8h]
  WNDCLASSA WndClass; // [esp+19Ch] [ebp-28h]

  InitializeCriticalSection(&CriticalSection);
  dword_404C64 = -1;
  s = -1;
  hWnd = 0;
  dword_404C5C = 0;
  dword_404C58 = 0;
  dword_404C80 = 0;
  type = 1;
  *(_DWORD *)&Args = 0;
  *(_DWORD *)&dword_407CA4 = 0;
  *(_DWORD *)&dword_407CB8 = 0;
  dword_404C7C = 0;
  dword_407CA0 = 32;
  SetConsoleCtrlHandler(HandlerRoutine, 1);
  sub_401000(Format);
  WndClass.hInstance = hInstance;
  WndClass.style = 0;
  WndClass.lpfnWndProc = (WNDPROC)&sub_401A70;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hIcon = 0;
  WndClass.hCursor = 0;
  WndClass.hbrBackground = 0;
  WndClass.lpszMenuName = 0;
  WndClass.lpszClassName = WindowName;
  RegisterClassA(&WndClass);
  hWnd = CreateWindowExA(
           0,
           WindowName,
           WindowName,
           0xCF0000u,
           2147483648,
           2147483648,
           2147483648,
           2147483648,
           0,
           0,
           hInstance,
           0);
  if ( !WSAStartup(1u, &WSAData) )
    return 1;
  sub_401000(aUnableToStartN);
  return 0;
}

int sub_4011FD()
{
  if ( hWnd )
  {
    DestroyWindow(hWnd);
    hWnd = 0;
  }
  if ( s != -1 )
  {
    shutdown(s, 2);
    closesocket(s);
    s = -1;
  }
  sub_40188E();
  DeleteCriticalSection(&CriticalSection);
  return WSACleanup();
}

signed int __cdecl sub_401250(signed int a1, char **a2)
{
  char *v2; // eax
  char v3; // bl
  int v4; // eax
  int v6; // [esp+Ch] [ebp-Ch]
  char *i; // [esp+10h] [ebp-8h]
  char v8; // [esp+17h] [ebp-1h]

  v8 = 0;
  if ( a1 < 4 )
  {
LABEL_60:
    sub_402113();
    return 0;
  }
  if ( a1 <= 1 )
    goto LABEL_56;
  do
  {
    ++a2;
    v2 = *a2;
    for ( i = *a2; ; v2 = i )
    {
      v3 = *v2;
      if ( !*v2 )
        break;
      if ( v8 )
      {
        v3 = v8;
        v8 = 0;
      }
      else
      {
        ++i;
        if ( v3 == 45 )
          v3 = *i++;
      }
      if ( v3 > 86 )
      {
        if ( v3 <= 114 )
        {
          if ( v3 != 114 )
          {
            if ( v3 != 99 )
            {
              if ( v3 == 104 )
                goto LABEL_60;
              if ( v3 == 105 )
                goto LABEL_32;
              if ( v3 != 108 )
                goto LABEL_45;
LABEL_28:
              if ( !sub_4014A8(&i, &v6) )
                goto LABEL_53;
              if ( v6 <= 0xFFFF )
                *(_DWORD *)&Args = v6;
              else
                sub_401000(aListeningPortN);
              continue;
            }
            goto LABEL_34;
          }
LABEL_38:
          if ( !sub_4014A8(&i, &v6) )
            goto LABEL_53;
          if ( v6 <= 0xFFFF )
            *(_DWORD *)&dword_407CB8 = v6;
          else
            sub_401000(aRemotePortNumb);
          continue;
        }
        if ( v3 != 115 )
        {
          if ( v3 != 117 )
          {
            if ( v3 != 118 )
              goto LABEL_45;
LABEL_46:
            dword_404C58 = 1;
            continue;
          }
          goto LABEL_47;
        }
      }
      else
      {
        if ( v3 == 86 )
          goto LABEL_46;
        if ( v3 <= 76 )
        {
          if ( v3 == 76 )
            goto LABEL_28;
          if ( v3 == 63 )
            goto LABEL_60;
          if ( v3 != 67 )
          {
            if ( v3 == 72 )
              goto LABEL_60;
            if ( v3 != 73 )
            {
LABEL_45:
              --i;
              dword_404C64 = sub_4014DC(&i);
              continue;
            }
LABEL_32:
            v4 = sub_4014DC(&i);
            if ( v4 != -1 )
            {
              dword_404C7C = v4;
              continue;
            }
LABEL_53:
            v8 = v3;
            continue;
          }
LABEL_34:
          if ( !sub_4014A8(&i, &v6) )
            goto LABEL_53;
          if ( v6 > 512 )
          {
            sub_401000(aTooManyConnect);
            v6 = 512;
          }
          dword_407CA0 = v6;
          continue;
        }
        if ( v3 == 82 )
          goto LABEL_38;
        if ( v3 != 83 )
        {
          if ( v3 != 85 )
            goto LABEL_45;
LABEL_47:
          dword_404C80 = 1;
          type = 2;
          continue;
        }
      }
      if ( !sub_4014A8(&i, &v6) )
        goto LABEL_53;
      if ( v6 <= 0xFFFF )
        *(_DWORD *)&dword_407CA4 = v6;
      else
        sub_401000(aSourceBindPort);
    }
    --a1;
  }
  while ( a1 > 1 );
LABEL_56:
  if ( dword_404C64 == -1 )
  {
    sub_401000(aNoIpAddressPro, a127001);
    i = a127001;
    dword_404C64 = sub_4014DC(&i);
  }
  return 1;
}

signed int __cdecl sub_4014A8(char **a1, int *a2)
{
  int v2; // ecx
  signed int result; // eax
  char *v4; // edx
  char v5; // bl

  v2 = 0;
  result = 0;
  v4 = *a1;
  do
  {
    v5 = *v4++;
    if ( v5 < 48 )
      break;
    if ( v5 > 57 )
      break;
    v2 = v5 + 10 * v2 - 48;
    result = 1;
  }
  while ( v5 <= 57 );
  *a1 = v4 - 1;
  *a2 = v2;
  return result;
}

int __cdecl sub_4014DC(char **a1)
{
  unsigned int v1; // ecx
  char v2; // al
  char *v3; // esi
  int result; // eax
  char cp[256]; // [esp+8h] [ebp-100h]

  v1 = 0;
  v2 = **a1;
  v3 = *a1 + 1;
  if ( v2 != 34 )
    goto LABEL_3;
  while ( 1 )
  {
    v2 = *v3++;
LABEL_3:
    if ( !v2 )
      break;
    if ( v2 == 44 || v2 == 58 || v2 == 34 || v2 == 32 || v1 >= 0xFF )
      break;
    cp[v1++] = v2;
  }
  cp[v1] = 0;
  result = sub_40153D(cp, 0);
  *a1 = v3 - 1;
  return result;
}

unsigned int __cdecl sub_40153D(char *cp, int a2)
{
  unsigned int v2; // edi
  struct hostent *v3; // eax
  int v4; // eax
  CHAR v6; // [esp+8h] [ebp-20h]

  v2 = -1;
  if ( cp && *cp )
  {
    v2 = inet_addr(cp);
    if ( v2 == -1 )
    {
      if ( a2 )
        *(_DWORD *)a2 = 0;
      sub_401047(aLookingUpHostn, cp);
      v3 = gethostbyname(cp);
      if ( v3 )
      {
        v2 = **(_DWORD **)v3->h_addr_list;
        v4 = sub_401A37(**(_DWORD **)v3->h_addr_list, &v6);
        sub_401047(aSResolvedToS, cp, v4);
      }
      else
      {
        sub_401000(aUnableToResolv, cp);
      }
    }
    else if ( a2 )
    {
      *(_DWORD *)a2 = 1;
    }
  }
  return v2;
}

signed int __usercall sub_4015C7@<eax>(int a1@<ebp>)
{
  int v1; // ecx
  _DWORD *i; // eax
  SOCKET v3; // eax
  int v4; // eax
  int v5; // eax
  int v7; // ST1C_4
  int v8; // eax
  SOCKET *v9; // edi
  SOCKET v10; // eax
  SOCKET v11; // esi
  SOCKET v12; // eax
  SOCKET v13; // esi
  int v14; // ST10_4
  int v15; // eax
  int v16; // [esp-4h] [ebp-28h]
  char optval[4]; // [esp+0h] [ebp-24h]
  CHAR v18; // [esp+4h] [ebp-20h]
  int v19; // [esp+1Ch] [ebp-8h]
  int v20; // [esp+20h] [ebp-4h]

  v1 = dword_407CA0;
  for ( i = &unk_404C90; v1; --v1 )
  {
    i[1] = -1;
    *i = -1;
    i += 6;
  }
  name.sa_family = 2;
  *(_WORD *)name.sa_data = htons(Args);
  *(_DWORD *)&name.sa_data[2] = dword_404C7C;
  to.sa_family = 2;
  *(_WORD *)to.sa_data = htons(dword_407CB8);
  *(_DWORD *)&to.sa_data[2] = dword_404C64;
  stru_407CA8.sa_family = 2;
  *(_WORD *)stru_407CA8.sa_data = htons(dword_407CA4);
  *(_DWORD *)&stru_407CA8.sa_data[2] = dword_404C7C;
  if ( dword_404C80 )
  {
    *(_DWORD *)optval = 1;
    v9 = (SOCKET *)sub_40196D();
    if ( !v9 )
    {
      sub_401000(aUnableToCreate_0);
      return 0;
    }
    v10 = socket(2, type, 0);
    v11 = v10;
    *v9 = v10;
    if ( v10 == -1 )
    {
      sub_401000(aUnableToCreate_1);
LABEL_21:
      sub_4018B5(v9);
      return 0;
    }
    if ( bind(v10, &name, 16) == -1 )
    {
      sub_401000(aUnableToBindTo_0, *(_DWORD *)&Args);
    }
    else
    {
      setsockopt(v11, 0xFFFF, 4, optval, 4);
      WSAAsyncSelect(v11, hWnd, 0xBD1u, 1);
      v12 = socket(2, type, 0);
      v13 = v12;
      v9[1] = v12;
      if ( v12 == -1 )
      {
        sub_401000(aUnableToCreate_2);
        goto LABEL_21;
      }
      if ( bind(v12, &stru_407CA8, 16) != -1 )
      {
        WSAAsyncSelect(v13, hWnd, 0xBD1u, 1);
        v14 = *(_DWORD *)&Args;
        v15 = sub_401A37(dword_404C7C, &v18);
        sub_401047(aListeningForUd, v15, v14);
        return 1;
      }
      sub_401000(aUnableToBindTo_0, *(_DWORD *)&dword_407CA4);
    }
    sub_4018B5(v9);
    return 0;
  }
  v20 = a1;
  v19 = 1;
  v3 = socket(2, type, 0);
  s = v3;
  if ( v3 == -1 )
  {
    v4 = WSAGetLastError();
    sub_401000(aUnableToCreate, aWinsockErrorCo, v4);
    return 0;
  }
  WSAAsyncSelect(v3, hWnd, 0xBD0u, 8);
  setsockopt(s, 0xFFFF, 4, (const char *)&v19, 4);
  if ( bind(s, &name, 16) == -1 )
  {
    v5 = WSAGetLastError();
    if ( v5 == 10048 )
      sub_401000(aTcpPortDIsAlre, *(_DWORD *)&Args);
    else
      sub_401000(aUnableToBindTo, *(_DWORD *)&Args, aWinsockErrorCo, v5);
    return 0;
  }
  listen(s, 1);
  v7 = *(_DWORD *)&Args;
  v8 = sub_401A37(dword_404C7C, (LPSTR)&v16);
  sub_401047(aListeningForTc, v8, v7);
  return 1;
}

int sub_40188E()
{
  unsigned int v0; // esi
  char *v1; // edi
  int result; // eax

  v0 = 0;
  v1 = (char *)&unk_404C90;
  if ( dword_407CA0 )
  {
    do
    {
      result = sub_4018B5(v1);
      v1 += 24;
      ++v0;
    }
    while ( v0 < dword_407CA0 );
  }
  return result;
}

void __cdecl sub_4018B5(SOCKET *a1)
{
  EnterCriticalSection(&CriticalSection);
  if ( a1 )
  {
    if ( a1[1] != -1 )
    {
      sub_401047(aClosingOutboun);
      shutdown(a1[1], 2);
      closesocket(a1[1]);
      if ( IsWindow(hWnd) )
        WSAAsyncSelect(a1[1], hWnd, 0, 0);
      a1[1] = -1;
    }
    if ( *a1 != -1 )
    {
      sub_401047(aClosingInbound);
      shutdown(*a1, 2);
      closesocket(*a1);
      if ( IsWindow(hWnd) )
        WSAAsyncSelect(*a1, hWnd, 0, 0);
      *a1 = -1;
    }
  }
  LeaveCriticalSection(&CriticalSection);
}

_DWORD *sub_40196D()
{
  _DWORD *v0; // esi
  _DWORD *v1; // ebp
  int v2; // ecx

  v0 = &unk_404C90;
  v1 = 0;
  EnterCriticalSection(&CriticalSection);
  v2 = 0;
  if ( dword_407CA0 )
  {
    while ( *v0 != -1 || v0[1] != -1 )
    {
      v0 += 6;
      if ( ++v2 >= (unsigned int)dword_407CA0 )
        goto LABEL_7;
    }
    v1 = v0;
    v0[2] = 0;
    v0[3] = 0;
    v0[4] = 0;
    v0[5] = 0;
  }
LABEL_7:
  LeaveCriticalSection(&CriticalSection);
  return v1;
}

_DWORD *__cdecl sub_4019BD(int a1, int a2)
{
  _DWORD *v2; // esi
  int v3; // ecx
  signed int v4; // edx
  _DWORD *v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]
  signed int v8; // [esp+1Ch] [ebp+8h]

  v6 = 0;
  v2 = &unk_404C90;
  EnterCriticalSection(&CriticalSection);
  v7 = 0;
  if ( dword_407CA0 )
  {
    v3 = a1;
    while ( 1 )
    {
      v8 = 0;
      v4 = 0;
      if ( v3 == *v2 || !v3 )
        v4 = 1;
      if ( a2 == v2[1] || !a2 )
        v8 = 1;
      if ( v4 && v8 )
        break;
      v2 += 6;
      if ( ++v7 >= (unsigned int)dword_407CA0 )
        goto LABEL_14;
    }
    v6 = v2;
  }
LABEL_14:
  LeaveCriticalSection(&CriticalSection);
  return v6;
}

LPSTR __cdecl sub_401A37(int a1, LPSTR a2)
{
  unsigned int v2; // eax

  v2 = (unsigned int)a1 >> 16;
  wsprintfA(a2, aDDDD, (unsigned __int8)a1, BYTE1(a1), BYTE2(a1), BYTE1(v2));
  return a2;
}

LRESULT __stdcall sub_401A70(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  int v5; // edi
  _DWORD *v6; // esi
  int v7; // ST20_4
  int v8; // ST20_4
  char *v9; // eax
  int v10; // ST20_4
  int v11; // ST20_4
  int v12; // ST20_4
  unsigned int v13; // edi
  SOCKET *v14; // esi
  SOCKET *v15; // esi
  char *v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *v19; // eax
  int v20; // ST20_4
  int v21; // ST18_4
  int v22; // ST10_4
  u_short v23; // ax
  SOCKET v24; // esi
  int v25; // ST20_4
  int v26; // ST20_4
  char *v27; // eax
  SOCKET *v28; // eax
  SOCKET v29; // esi
  int v30; // ST20_4
  char *v31; // eax
  int v32; // eax
  int v33; // ST20_4
  char *v34; // eax
  int v35; // ST20_4
  int v36; // ST1C_4
  char *v37; // eax
  int v38; // ST20_4
  int v39; // esi
  SOCKET *v40; // edi
  int v41; // ST20_4
  int v42; // ST20_4
  int v43; // ST20_4
  int v44; // ST20_4
  char buf; // [esp+Ch] [ebp-8D0h]
  CHAR v46; // [esp+80Ch] [ebp-D0h]
  CHAR String1; // [esp+82Ch] [ebp-B0h]
  CHAR v48; // [esp+84Ch] [ebp-90h]
  CHAR v49; // [esp+86Ch] [ebp-70h]
  struct sockaddr v50; // [esp+88Ch] [ebp-50h]
  struct sockaddr v51; // [esp+89Ch] [ebp-40h]
  struct sockaddr v52; // [esp+8ACh] [ebp-30h]
  struct sockaddr name; // [esp+8BCh] [ebp-20h]
  struct sockaddr from; // [esp+8CCh] [ebp-10h]
  SOCKET *Msga; // [esp+8E8h] [ebp+Ch]

  switch ( Msg )
  {
    case 2u:
      ::hWnd = 0;
      PostQuitMessage(0);
      return 0;
    case 0xBD0u:
      v13 = (unsigned int)lParam >> 16;
      switch ( (unsigned __int16)lParam )
      {
        case 1u:
          if ( v13 )
          {
            sub_401000(aErrorDOccurred_10, (unsigned int)lParam >> 16);
            return 0;
          }
          lParam = 16;
          v39 = recvfrom(wParam, &buf, 2048, 0, &from, &lParam);
          v40 = sub_4019BD(wParam, 0);
          if ( v40 )
          {
            if ( v39 == -1 )
            {
              v41 = WSAGetLastError();
              sub_401000(aErrorDOccurred_6, v41);
            }
            else
            {
              sub_401047(aDBytesReceived_1);
              if ( send(v40[1], &buf, v39, 0) != -1 )
                return 0;
              v42 = WSAGetLastError();
              sub_401000(aErrorDOccurred_7, v42);
            }
          }
          else
          {
            v40 = sub_4019BD(0, wParam);
            if ( !v40 )
              return 0;
            if ( v39 == -1 )
            {
              v43 = WSAGetLastError();
              sub_401000(aErrorDOccurred_8, v43);
            }
            else
            {
              sub_401047(aDBytesReceived_2);
              if ( send(*v40, &buf, v39, 0) != -1 )
                return 0;
              v44 = WSAGetLastError();
              sub_401000(aErrorDOccurred_9, v44);
            }
          }
          sub_4018B5(v40);
          return 0;
        case 8u:
          if ( wParam == s )
          {
            if ( v13 )
            {
              v38 = WSAGetLastError();
              sub_401000(aErrorDOccurred_5, v38);
            }
            else
            {
              lParam = 16;
              v24 = accept(wParam, &from, &lParam);
              if ( v24 == -1 )
              {
                v25 = WSAGetLastError();
                sub_401000(aErrorDOccurred_4, v25);
              }
              else
              {
                wParam = 1;
                v26 = ntohs(*(u_short *)from.sa_data);
                v27 = inet_ntoa(*(struct in_addr *)&from.sa_data[2]);
                sub_401047(aConnectionAcce, v27, v26);
                v28 = sub_40196D();
                Msga = v28;
                if ( v28 )
                {
                  *v28 = v24;
                  v29 = socket(2, type, 0);
                  if ( v29 == -1 )
                  {
                    sub_401000(aUnableToCreate_3);
                    sub_4018B5(Msga);
                  }
                  else
                  {
                    Msga[1] = v29;
                    setsockopt(v29, 0xFFFF, 4, (const char *)&wParam, 4);
                    if ( bind(v29, &stru_407CA8, 16) == -1 )
                    {
                      sub_401000(aUnableToBindTo_1, *(_DWORD *)&dword_407CA4);
                      sub_4018B5(Msga);
                    }
                    else
                    {
                      WSAAsyncSelect(v29, ::hWnd, 0xBD0u, 48);
                      v30 = ntohs(*(u_short *)from.sa_data);
                      v31 = inet_ntoa(*(struct in_addr *)&from.sa_data[2]);
                      sub_401047(aAttemptingToCo, v31, v30);
                      if ( connect(v29, &to, 16) == -1 )
                      {
                        v32 = WSAGetLastError();
                        if ( v32 != 10035 )
                        {
                          if ( v32 == 10048 )
                          {
                            v33 = *(_DWORD *)&dword_407CB8;
                            v34 = inet_ntoa(*(struct in_addr *)&from.sa_data[2]);
                            sub_401000(aSSPortDAddress, aUnableToConnec, v34, v33);
                          }
                          else
                          {
                            v35 = v32;
                            v36 = *(_DWORD *)&dword_407CB8;
                            v37 = inet_ntoa(*(struct in_addr *)&from.sa_data[2]);
                            sub_401000(aSSPortDErrorD, aUnableToConnec, v37, v36, v35);
                          }
                          sub_4018B5(Msga);
                        }
                      }
                    }
                  }
                }
                else
                {
                  sub_401000(aUnableToCreate_0);
                }
              }
            }
          }
          return 0;
        case 0x10u:
          v15 = sub_4019BD(0, wParam);
          if ( v15 )
          {
            if ( v13 )
            {
              if ( v13 == 10048 )
                sub_401000(aSAddressIsAlre, aUnableToConnec);
              else
                sub_401000(aSErrorD, aUnableToConnec, v13);
              sub_4018B5(v15);
            }
            else
            {
              lParam = 16;
              getpeername(*v15, &name, &lParam);
              v16 = inet_ntoa(*(struct in_addr *)&name.sa_data[2]);
              lstrcpyA(&String1, v16);
              lParam = 16;
              getsockname(*v15, &v52, &lParam);
              v17 = inet_ntoa(*(struct in_addr *)&v52.sa_data[2]);
              lstrcpyA(&v48, v17);
              lParam = 16;
              getsockname(v15[1], &v51, &lParam);
              v18 = inet_ntoa(*(struct in_addr *)&v51.sa_data[2]);
              lstrcpyA(&v46, v18);
              lParam = 16;
              getpeername(v15[1], &v50, &lParam);
              v19 = inet_ntoa(*(struct in_addr *)&v50.sa_data[2]);
              lstrcpyA(&v49, v19);
              v20 = ntohs(*(u_short *)v50.sa_data);
              v21 = ntohs(*(u_short *)v51.sa_data);
              v22 = ntohs(*(u_short *)v52.sa_data);
              v23 = ntohs(*(u_short *)name.sa_data);
              sub_401000(aPipeConnectedI, &String1, v23, &v48, v22, &v46, v21, &v49, v20);
              WSAAsyncSelect(*v15, ::hWnd, 0xBD0u, 33);
              WSAAsyncSelect(v15[1], ::hWnd, 0xBD0u, 33);
            }
          }
          return 0;
        case 0x20u:
          v14 = sub_4019BD(wParam, 0);
          if ( v14 )
          {
            sub_401047(aInboundConnect);
          }
          else
          {
            v14 = sub_4019BD(0, wParam);
            if ( !v14 )
              return 0;
            sub_401047(aOutboundConnec);
          }
          sub_4018B5(v14);
          return 0;
      }
      break;
    case 0xBD1u:
      if ( (unsigned __int16)lParam == 1 )
      {
        if ( (unsigned int)lParam >> 16 )
        {
          sub_401000(aErrorDOccurred_3, (unsigned int)lParam >> 16);
        }
        else
        {
          lParam = 16;
          v5 = recvfrom(wParam, &buf, 2048, 0, &from, &lParam);
          v6 = sub_4019BD(wParam, 0);
          if ( v6 )
          {
            if ( v5 == -1 )
            {
              v7 = WSAGetLastError();
              sub_401000(aErrorDOccurred, v7);
            }
            else
            {
              sub_401047(aDBytesReceived);
              if ( *(_DWORD *)&from.sa_data[2] != v6[3] || *(_WORD *)from.sa_data != *((_WORD *)v6 + 5) )
              {
                *(struct sockaddr *)(v6 + 2) = from;
                v8 = ntohs(*((_WORD *)v6 + 5));
                v9 = inet_ntoa((struct in_addr)v6[3]);
                sub_401047(aSettingLastUdp, v9, v8);
              }
              if ( sendto(v6[1], &buf, v5, 0, &to, 16) != -1 )
                return 0;
              v10 = WSAGetLastError();
              sub_401000(aErrorDOccurred_0, v10);
            }
            goto LABEL_22;
          }
          v6 = sub_4019BD(0, wParam);
          if ( v6 )
          {
            if ( v5 == -1 )
            {
              v11 = WSAGetLastError();
              sub_401000(aErrorDOccurred_1, v11);
LABEL_22:
              sub_4018B5(v6);
              return 0;
            }
            sub_401047(aDBytesReceived_0, v5);
            if ( v6[3] && *((_WORD *)v6 + 5) )
            {
              if ( sendto(*v6, &buf, v5, 0, (const struct sockaddr *)(v6 + 2), 16) == -1 )
              {
                v12 = WSAGetLastError();
                sub_401000(aErrorDOccurred_2, v12);
                goto LABEL_22;
              }
            }
            else
            {
              sub_401000(aDataReceivedFr);
            }
          }
        }
      }
      break;
    default:
      return DefWindowProcA(hWnd, Msg, wParam, lParam);
  }
  return 0;
}

BOOL __stdcall HandlerRoutine(DWORD CtrlType)
{
  BOOL result; // eax

  if ( !dword_404C5C )
  {
    sub_401000(aQuitSignalDete);
    PostMessageA(hWnd, 0x10u, 0, 0);
  }
  result = 1;
  dword_404C5C = 1;
  return result;
}

void sub_402113()
{
  sub_401000(aSHvuLrsPortIIp, WindowName);
  sub_401000(aHShowsThisHelp);
  sub_401000(aCMaximumAllowe, 32);
  sub_401000(aIListeningInte);
  sub_401000(aLListeningPort);
  sub_401000(aRRemotePortNum);
  sub_401000(aSOutboundSourc);
  sub_401000(aUUdpMode);
  sub_401000(aVVerboseMode);
  sub_401000(aExample);
  sub_401000(aFpipeL53S53R80);
  sub_401000(aThisWouldSetTh);
  sub_401000(aWhenALocalConn);
  sub_401000(aMadeToPort80Of);
  sub_401000(aSourcePortForT);
  sub_401000(aDataSentToAndF);
}

void __noreturn start()
{
  int v0; // eax
  char **argv; // [esp+10h] [ebp-2Ch]
  int v2; // [esp+14h] [ebp-28h]
  int v3; // [esp+18h] [ebp-24h]
  char **envp; // [esp+1Ch] [ebp-20h]
  int argc; // [esp+20h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+24h] [ebp-18h]

  ms_exc.registration.TryLevel = 0;
  _set_app_type(1);
  dword_407CCC = -1;
  dword_407CD0 = -1;
  *(_DWORD *)_p__fmode() = dword_407CC8;
  *(_DWORD *)_p__commode() = dword_407CC4;
  dword_407CD4 = adjust_fdiv;
  nullsub_1();
  if ( !dword_404C38 )
    _setusermatherr(sub_402308);
  _setdefaultprecision();
  initterm(&unk_404008, &unk_40400C);
  v2 = dword_407CC0;
  _getmainargs(&argc, &argv, &envp, dword_407CBC, &v2);
  initterm(&unk_404000, &unk_404004);
  *(_DWORD *)_p___initenv() = envp;
  v0 = main(argc, (const char **)argv, (const char **)envp);
  v3 = v0;
  exit(v0);
}

int XcptFilter()
{
  return _XcptFilter();
}

int __cdecl initterm(int a1, int a2)
{
  return _initterm(a1, a2);
}

unsigned int _setdefaultprecision()
{
  return controlfp(0x10000u, 0x30000u);
}

int sub_402308()
{
  return 0;
}

unsigned int __cdecl controlfp(unsigned int NewValue, unsigned int Mask)
{
  return _controlfp(NewValue, Mask);
}
