#include <stdio.h>
#include <tchar.h>
#include <string.h>
//специфичные заголовки для использования анклава
#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Lab3_enclave_u.h"
#define ENCLAVE_FILE _T("Lab3_enclave.signed.dll")

#define BUF_LEN 100 //длина буфера обмена между анкалавом и небезопасным приложением


int main()
{
	char buffer[BUF_LEN] = { 0 };

	//активация анклава
	sgx_enclave_id_t eid; //идентификация анклава
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 }; 
	int updated = 0;
	

	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL); //путь к файлу с enclave, флаг отладки, указатель на токен запуска, указатель на переменную updated, указатель на переменную eid и указатель на переменную для сохранения информации об ошибке(NULL).
	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return - 1;
	}

	while (true)  //в цикле запрашивается у пользователя индекс (idx) для получения данных из enclave или -1 для выхода из программы.
	{
		printf("Input index to retrieve, or -1 to exit: \t");
		int idx = -1;
		scanf_s("%d", &idx); //целочисленное чтение из потока ввода и запись в переменную,если не целочисленное-ошибка
		if (idx < 0) {
			return 0;
		}
		foo(eid, buffer, BUF_LEN, idx);//добавить eID
		printf("%s\n====================\n\n", buffer); //вывод буфера
	}
	//выгрузить анклав
	if (SGX_SUCCESS != sgx_destroy_enclave(eid));
	return -1; //не равен
	return 0;  //равен 
}
