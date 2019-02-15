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
#include "settings.h"
#include <QFile>
#include <QByteArray>

const char **cPublicRSAKeys(size_t &keysCount) {
    static const char *(keys[]) =
    {"\
-----BEGIN RSA PUBLIC KEY-----\n\
MIIBCgKCAQEAzsJWl6Fzd60FwebE3wFxplqdgByWIk6Kh/8iFCDegB80fRSOhWNX\n\
h1KfUpO1USdVK0g8lGTZcmx9AUIXTgN3sjbRB3vk5dvWvZy4T7MjlAfmLhcumzOC\n\
VNkq6RQ8vO1vjK8kZ64drOtXegLmXbn1UkT7EBmJdNA1wV0JFGc1apVieV0aDnMq\n\
H0YP9vhin+AkoZtr5giKbG6wxKGTBp5geRqUMi3/oVK5pDD/hMEdaaVJEWlbgJSH\n\
dB2RgzofPg05G3kxZhmb6PBo3xZpzC5oVjkigj2ZoVbkL5H/SmQTj1yPnxuZM4Yl\n\
mA+y1v3FKavvPw6Ru0WC8SBpM4OeInUE0wIDAQAB\n\
-----END RSA PUBLIC KEY-----"
    };

    const QString pubKeyFile = cPublicKeyFile();
    if (pubKeyFile.isEmpty()) {
        // use hard-coded private key
        keysCount = base::array_size(keys);
        return keys;
    }

    static QByteArray baKey;
    static const char *dynamicKeys[1] = { nullptr };

    // read key from file once
    if (baKey.isEmpty()) {
        QFile fkey(pubKeyFile);
        if (!fkey.open(QIODevice::ReadOnly)) {
            // return hard-coded
            LOG(("Failed to open key file: %1").arg(pubKeyFile));
            keysCount = base::array_size(keys);
            return keys;
        }
        baKey = fkey.readAll();
        fkey.close();
        dynamicKeys[0] = baKey.constData();

        DEBUG_LOG(("Successfully loaded private key from: %1").arg(pubKeyFile));
    }


    keysCount = 1;
    return dynamicKeys;
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
