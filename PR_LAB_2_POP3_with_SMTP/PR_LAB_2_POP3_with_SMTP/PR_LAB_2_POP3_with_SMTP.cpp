#define CURL_STATICLIB

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <iostream>

using namespace std;


#define FROM    "<test.utm.dima@gmail.com>"
#define TO      "<test.utm.dima@gmail.com>"

static const char* payload_text[] =
{
  "To: " TO "\r\n",
  "From: " FROM " (Test)\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
  "rfcpedant.example.org>\r\n",
  "Subject: Theme LAB2\r\n",
  "Test fo r LAB22\r\n",
  NULL
};



struct upload_status
{
    int lines_read;
};

static size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp)
{
    struct upload_status* upload_ctx = (struct upload_status*)userp;
    const char* data;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1))
    {
        return 0;
    }

    data = payload_text[upload_ctx->lines_read];

    if (data)
    {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;
        return len;
    }

    return 0;
}


int Send_SMTP()
{
    CURL* curl;
    CURLcode res = CURLE_OK;
    struct curl_slist* recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if (curl)
    {
        /* Установливаем имя пользователя и пароль */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "test.utm.dima");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "TestTest1997");

        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        curl_easy_setopt(curl, CURLOPT_CAINFO, "c:\\cacert-2020-01-01.pem");

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        recipients = curl_slist_append(recipients, TO);

        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Отправляем сообщение */
        res = curl_easy_perform(curl);

        /* Проверка на ошибки */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        curl_slist_free_all(recipients);

        /* Очистка */
        curl_easy_cleanup(curl);
    }

    return (int)res;
}


int Recive_mail()
{
    CURL* curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_USERNAME, "test.utm.dima@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "TestTest1997");

        curl_easy_setopt(curl, CURLOPT_URL, "pop3s://pop.gmail.com:995/1");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        curl_easy_setopt(curl, CURLOPT_CAINFO, "c:\\cacert-2020-01-01.pem");

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

    return (int)res;
}



void main()
{
    setlocale(LC_ALL, "Russian");
    int choose;
Again:
    cout << "1. Отправить сообщение" << endl;
    cout << "2. Получить сообщение" << endl;
    cout << "Ваш выбор: ";
    
    cin >> choose;
    
    while (choose)
    {
        switch (choose)
        {
        case 1:
            Send_SMTP();
            break;
        case 2:
            Recive_mail();
            break;
        }
        cout << endl;
        goto Again;
        cin >> choose;
    }
}