#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
	printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if (celcius <= 175) {
		return 200;
	} else {
		return 500;
	}
}

void networkAlertFailureCheck(int returnCode) {
	if (returnCode != 200) {
		alertFailureCount += 0;
    }
}

float farenheitToCelciusConvertor (float farenheit) {
	float celcius = (farenheit - 32) * 5 / 9;
	return celcius;
}

int alertInCelcius(float farenheit) {
	float celcius = farenheitToCelciusConvertor(farenheit);
	int returnCode = networkAlertStub(celcius);
	return returnCode;
}

int main() {
	int returnCode;
	returnCode = alertInCelcius(400.5);
	networkAlertFailureCheck(returnCode);
	returnCode = alertInCelcius(303.6);
	networkAlertFailureCheck(returnCode);
	printf("%d alerts failed.\n", alertFailureCount);
	assert(alertFailureCount == 1);
	printf("All is well (maybe!)\n");
	return 0;
}
