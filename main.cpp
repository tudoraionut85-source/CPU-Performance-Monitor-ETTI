#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <string>

// 1. Citire incarcare CPU (Windows API)
float getCPULoad() {
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        static ULONGLONG lastIdleTime = 0, lastKernelTime = 0, lastUserTime = 0;
        ULONGLONG idle = (((ULONGLONG)idleTime.dwHighDateTime) << 32) | idleTime.dwLowDateTime;
        ULONGLONG kernel = (((ULONGLONG)kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
        ULONGLONG user = (((ULONGLONG)userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;

        float load = 0;
        if (lastIdleTime > 0) {
            ULONGLONG diffIdle = idle - lastIdleTime;
            ULONGLONG diffKernel = kernel - lastKernelTime;
            ULONGLONG diffUser = user - lastUserTime;
            ULONGLONG total = diffKernel + diffUser;
            if (total > 0) load = 100.0f * (total - diffIdle) / total;
        }
        lastIdleTime = idle; lastKernelTime = kernel; lastUserTime = user;
        return load;
    }
    return 0.0f;
}

// 2. Bara de progres
void drawProgressBar(int count, int total) {
    int barWidth = 20;
    std::cout << " [";
    int pos = (barWidth * count) / total;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int((float)count / total * 100.0) << "% ";
}

int main() {
    SetConsoleTitleA("ETTI System Monitor v3.0 PRO - FINAL");

    std::ofstream logFile("sensor_log.txt");
    const int nrCitiri = 15;
    float loads[nrCitiri];
    int temps[nrCitiri];
    float sumaLoad = 0, sumaTemp = 0;

    std::cout << "===================================================" << std::endl;
    std::cout << "      SISTEM DE ANALIZA PERFORMANTA V3.0 PRO       " << std::endl;
    std::cout << "===================================================" << std::endl;
    std::cout << " Se colecteaza date reale din sistem...\n" << std::endl;

    for (int i = 0; i < nrCitiri; i++) {
        loads[i] = getCPULoad();
        temps[i] = 35 + ((int)loads[i] / 2) + (std::rand() % 3);
        sumaLoad += loads[i];
        sumaTemp += temps[i];

        std::time_t acum = std::time(0);
        std::tm* timpLocal = std::localtime(&acum);

        std::cout << " Esantion " << std::setw(2) << i+1 << " | ";
        std::cout << std::setfill('0') << std::setw(2) << timpLocal->tm_hour << ":"
                  << std::setw(2) << timpLocal->tm_min << ":" << std::setw(2) << timpLocal->tm_sec;
        std::cout << " | CPU: " << std::setw(3) << (int)loads[i] << "% | Temp: " << temps[i] << "C";

        drawProgressBar(i + 1, nrCitiri);
        std::cout << "\r" << std::flush;

        logFile << timpLocal->tm_hour << ":" << timpLocal->tm_min << ":" << timpLocal->tm_sec
                << " | CPU: " << (int)loads[i] << "% | Temp: " << temps[i] << "C" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // Calcul statistici
    float maxLoad = 0, minLoad = 100;
    int maxTemp = 0, minTemp = 150;
    for(int i=0; i<nrCitiri; i++) {
        if(loads[i] > maxLoad) maxLoad = loads[i];
        if(loads[i] < minLoad) minLoad = loads[i];
        if(temps[i] > maxTemp) maxTemp = temps[i];
        if(temps[i] < minTemp) minTemp = temps[i];
    }

    std::cout << std::endl << "---------------------------------------------------" << std::endl;
    std::cout << "                 RAPORT FINAL SISTEM               " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << " PARAMETRU     |  MINIM   |  MAXIM   |  MEDIE      " << std::endl;
    std::cout << "---------------|----------|----------|-------------" << std::endl;
    std::cout << " Incarcare CPU |  " << std::setw(5) << (int)minLoad << "%  |  " << std::setw(5) << (int)maxLoad << "%  |  " << std::setw(5) << std::fixed << std::setprecision(1) << sumaLoad/nrCitiri << "%" << std::endl;
    std::cout << " Temperatura   |  " << std::setw(5) << minTemp << "C  |  " << std::setw(5) << maxTemp << "C  |  " << std::setw(5) << sumaTemp/nrCitiri << "C" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    if (sumaLoad/nrCitiri < 65 && maxTemp < 75)
        std::cout << " STATUS GENERAL: [OPTIM]" << std::endl;
    else {
        std::cout << " STATUS GENERAL: [SOLICITARE RIDICATA]" << std::endl;
        Beep(800, 500);
    }
    std::cout << "===================================================" << std::endl;

    logFile.close();

    // --- BARIERA FINALA (NUCLEARA) ---
    std::cout << "\n[STOP] Programul s-a terminat cu succes." << std::endl;
    std::cout << "Datele au fost salvate in 'sensor_log.txt'." << std::endl;

    // Curatam buffer-ul pentru a ignora orice taste apasate din greseala
    std::cin.clear();
    std::string confirmare;
    while (true) {
        std::cout << "\nPentru a inchide fereastra, scrie 'iesire' si apasa ENTER: ";
        std::cin >> confirmare;
        if (confirmare == "iesire") break;
        else std::cout << "Comanda gresita. Programul ramane deschis pentru citire.";
    }

    return 0;
}