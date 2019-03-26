//
// This file is part of Kepka,
// an unofficial desktop version of Telegram messaging app,
// see https://github.com/procxx/kepka
//
// Kepka is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// It is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// In addition, as a special exception, the copyright holders give permission
// to link the code of portions of this program with the OpenSSL library.
//
// Full license: https://github.com/procxx/kepka/blob/master/LICENSE
// Copyright (c) 2018- Kepka Contributors, https://github.com/procxx
//

#include "config.h"
#include "core/utils.h"

//#define OFFICIAL_SERVER
#ifdef OFFICIAL_SERVER

const char **cPublicRSAKeys(size_t &keysCount) {
	static const char *(keys[]) = {
	    "\
-----BEGIN RSA PUBLIC KEY-----\n\
MIIBCgKCAQEAwVACPi9w23mF3tBkdZz+zwrzKOaaQdr01vAbU4E1pvkfj4sqDsm6\n\
lyDONS789sVoD/xCS9Y0hkkC3gtL1tSfTlgCMOOul9lcixlEKzwKENj1Yz/s7daS\n\
an9tqw3bfUV/nqgbhGX81v/+7RFAEd+RwFnK7a+XYl9sluzHRyVVaTTveB2GazTw\n\
Efzk2DWgkBluml8OREmvfraX3bkHZJTKX4EQSjBbbdJ2ZXIsRrYOXfaA+xayEGB+\n\
8hdlLmAjbCVfaigxX0CDqWeR1yFL9kwd9P0NsZRPsmoqVwMbMu7mStFai6aIhc3n\n\
Slv8kg9qv1m6XHVQY3PnEw+QQtqSIXklHwIDAQAB\n\
-----END RSA PUBLIC KEY-----"};
	keysCount = base::array_size(keys);
	return keys;
}

static const BuiltInDc _builtInDcs[] = {{1, "149.154.175.50", 443},
                                        {2, "149.154.167.51", 443},
                                        {3, "149.154.175.100", 443},
                                        {4, "149.154.167.91", 443},
                                        {5, "149.154.171.5", 443}};

static const BuiltInDc _builtInDcsIPv6[] = {{1, "2001:b28:f23d:f001::a", 443},
                                            {2, "2001:67c:4e8:f002::a", 443},
                                            {3, "2001:b28:f23d:f003::a", 443},
                                            {4, "2001:67c:4e8:f004::a", 443},
                                            {5, "2001:b28:f23f:f005::a", 443}};

static const BuiltInDc _builtInTestDcs[] = {
    {1, "149.154.175.10", 443}, {2, "149.154.167.40", 443}, {3, "149.154.175.117", 443}};

static const BuiltInDc _builtInTestDcsIPv6[] = {
    {1, "2001:b28:f23d:f001::e", 443}, {2, "2001:67c:4e8:f002::e", 443}, {3, "2001:b28:f23d:f003::e", 443}};

const BuiltInDc *builtInDcs() {
	return cTestMode() ? _builtInTestDcs : _builtInDcs;
}

int builtInDcsCount() {
	return (cTestMode() ? sizeof(_builtInTestDcs) : sizeof(_builtInDcs)) / sizeof(BuiltInDc);
}

const BuiltInDc *builtInDcsIPv6() {
	return cTestMode() ? _builtInTestDcsIPv6 : _builtInDcsIPv6;
}

int builtInDcsCountIPv6() {
	return (cTestMode() ? sizeof(_builtInTestDcsIPv6) : sizeof(_builtInDcsIPv6)) / sizeof(BuiltInDc);
}

#else

#include "settings.h"

const char **cPublicRSAKeys(size_t &keysCount) {
    static const char *(keys[]) = {
        "\
-----BEGIN RSA PUBLIC KEY-----\n\
MIIBCgKCAQEAuKrDihIICkmRUIAJYGvNQAnFgDjMKHv1XDAs34mfkk6J/k+laypb\n\
s9v/gqHbbiOZYPwrTyGCFCFitOkAxLs1PwA00KYn0NtOo67UweScYtpt/Ukq04RG\n\
OsSXQ6wBuGOJiERpOIJDlpQHiMKrh56K8D9nEJxeSwL8bjuBRzX8Udap5NxFlBHu\n\
lF9QZ2j4co/deZawSBTNzrinoxZRuEkB8OowUgcNp2/19sETFwoTBIx4qKJSRXWX\n\
aSnWaJoT9yM/XoBq3dr+bKKlOiWWjjQWruYne+bYAnk5W3lUCg3/mQgOCfj+52Rw\n\
lIKlq4EhJ9ziky61d0exh0oLktRAxGvlSwIDAQAB\n\
-----END RSA PUBLIC KEY-----"};
    keysCount = base::array_size(keys);
    return keys;
}

const BuiltInDc *builtInDcs() {
    static const QByteArray serverAddress = cServerIpAddress();
    if (serverAddress.isEmpty()) {
        static const BuiltInDc _builtInDcs[] = {{1, "127.0.0.1", 10443u}};
        return _builtInDcs;
    } else {
        static const int separatorIndex = serverAddress.indexOf(':');
        static const QByteArray addressData = separatorIndex < 0
                ? serverAddress
                : serverAddress.left(separatorIndex);

        static const quint16 port = separatorIndex < 0
                ? 10443u
                : serverAddress.mid(separatorIndex + 1).toUShort();
        static const BuiltInDc dynamicDcOption = { 1, addressData.constData(), port };
        static const BuiltInDc dynamicDcs[] = { dynamicDcOption };
        return dynamicDcs;
    }
}

int builtInDcsCount() { return 1; }
const BuiltInDc *builtInDcsIPv6() { return nullptr; }
int builtInDcsCountIPv6() { return 0; }

#endif
