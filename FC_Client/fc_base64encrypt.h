#ifndef BASE64ENCRYPT_H
#define BASE64ENCRYPT_H

#include <iostream>
#include <vector>



class Base64Encrypt
{
public:
    Base64Encrypt() : _groupLength(0) {}
    Base64Encrypt(const void *input, size_t length) : Base64Encrypt()
    {
        Update(input, length);
    }

    void Update(const void *input, size_t length)
    {
        static const size_t LEN = 3;
        _buf.reserve(_buf.size() + (length - (LEN - _groupLength) + LEN - 1) / LEN * 4 + 1);
        const unsigned char *buff = reinterpret_cast<const unsigned char *>(input);
        unsigned int i;

        for (i = 0; i < length; ++i)
        {
            _group[_groupLength++] = buff[i];
            if (_groupLength == LEN)
            {
                Encode();
            }
        }
    }
    const unsigned char *CipherText()
    {
        Final();
        return _buf.data();
    }
    std::string GetString()
    {
        const char *pstr = (const char *)CipherText();
        size_t length = GetSize();
        return std::string(pstr, length);
    }
    void Reset()
    {
        _buf.clear();
        _groupLength = 0;
        for (unsigned int i = 0; i < sizeof(_group) / sizeof(_group[0]); ++i)
        {
            _group[i] = 0;
        }
    }
    size_t GetSize()
    {
        CipherText();
        return _buf.size();
    }

private:
    Base64Encrypt(const Base64Encrypt &) = delete;
    Base64Encrypt & operator = (const Base64Encrypt &) = delete;

    void Encode()
    {
        unsigned char index;

        // 0 index byte
        index = _group[0] >> 2;
        _buf.push_back(Base64EncodeMap[index]);
        // 1 index byte
        index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
        _buf.push_back(Base64EncodeMap[index]);
        // 2 index byte
        index = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
        _buf.push_back(Base64EncodeMap[index]);
        // 3 index byte
        index = _group[2] & 0x3F;
        _buf.push_back(Base64EncodeMap[index]);

        _groupLength = 0;
    }
    void Final()
    {
        unsigned char index;

        if (_groupLength == 1)
        {
            _group[1] = 0;
            // 0 index byte
            index = _group[0] >> 2;
            _buf.push_back(Base64EncodeMap[index]);
            // 1 index byte
            index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
            _buf.push_back(Base64EncodeMap[index]);
            // 2 index byte
            _buf.push_back('=');
            // 3 index byte
            _buf.push_back('=');
        }
        else if (_groupLength == 2)
        {
            _group[2] = 0;
            // 0 index byte
            index = _group[0] >> 2;
            _buf.push_back(Base64EncodeMap[index]);
            // 1 index byte
            index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
            _buf.push_back(Base64EncodeMap[index]);
            // 2 index byte
            index = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
            _buf.push_back(Base64EncodeMap[index]);
            // 3 index byte
            _buf.push_back('=');
        }

        _groupLength = 0;
    }

private:
    std::vector<unsigned char> _buf;
    unsigned char _group[3];
    int _groupLength;

    static const unsigned char Base64EncodeMap[64];
};

const unsigned char Base64Encrypt::Base64EncodeMap[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

#endif // BASE64ENCRYPT_H
