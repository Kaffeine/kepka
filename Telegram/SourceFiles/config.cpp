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

const char **cPublicRSAKeys(size_t &keysCount) {

static const char *(keys[]) = {"\
-----BEGIN RSA PUBLIC KEY-----\n\
MIIBCgKCAQEAvx6OqhZqaB5xuSJqe32JRq/uN9j85FbtVsywXcea76eF0HnBZ04p\n\
IBHSncrNp1ad/MAZ70Sp0zk3tDSbGQQqUI3pQRyEq9OuPdBBWnpqhbkkFkYzXhnq\n\
UCZ0BuxdDNd88dWRZBE0IZxRXjE3QXaLcbnbns8aAwuYlQvBcWScghQWdoZXkseY\n\
hcs9AToTU5gVSptIlVnwnPp+TbYu3bzfas2vs9BZ2MSampHfGOkslN61ObxraSe2\n\
ui/AaRxpAIbK/2vvBquaJxVgzj6QPjOjZtPYJ+MGmXuo6/7TeGZPOhTu7Vt1g7RR\n\
BUTggR65bFKkmqKmgyNNDKo4wF6bY2rJuQIDAQAB\n\
-----END RSA PUBLIC KEY-----"};
            keysCount = base::array_size(keys);
            return keys;
}

static const BuiltInDc _builtInDcs[] = {
    { 1, "127.0.0.1", 11441 },
    { 2, "127.0.0.2", 11442 },
    { 3, "127.0.0.3", 11443 }
};

static const BuiltInDc _builtInDcsIPv6[] = {
    { 1, "20zzz:b28:f23d:f001::a", 443 },
    { 2, "20zzz:67c:4e8:f002::a", 443 },
    { 3, "20zzz:b28:f23d:f003::a", 443 },
};

static const BuiltInDc _builtInTestDcs[] = {
        { 1, "149.154.175.10", 443 },
        { 2, "149.154.167.40", 443 },
        { 3, "149.154.175.117", 443 }
};

static const BuiltInDc _builtInTestDcsIPv6[] = {
        { 1, "2001:b28:f23d:f001::e", 443 },
        { 2, "2001:67c:4e8:f002::e", 443 },
        { 3, "2001:b28:f23d:f003::e", 443 }
};

const BuiltInDc *builtInDcs()
{
    return cTestMode() ? _builtInTestDcs : _builtInDcs;
}

int builtInDcsCount()
{
    return (cTestMode() ? sizeof(_builtInTestDcs) : sizeof(_builtInDcs)) / sizeof(BuiltInDc);
}

const BuiltInDc *builtInDcsIPv6()
{
    return cTestMode() ? _builtInTestDcsIPv6 : _builtInDcsIPv6;
}

int builtInDcsCountIPv6()
{
    return (cTestMode() ? sizeof(_builtInTestDcsIPv6) : sizeof(_builtInDcsIPv6)) / sizeof(BuiltInDc);
}
