//E16ANA_STSADCCalibration.hh 240627 by R.Yamada
//    Last modified at <2024-06-27 20:33:31 >
//

#ifndef E16ANA_STSADCCALIBRATION_HH
#define E16ANA_STSADCCALIBRATION_HH

#include <string>
#include <vector>
#include <cstdint>

class E16ANA_STSADCCalibration {
public:
    E16ANA_STSADCCalibration();
    ~E16ANA_STSADCCalibration();

    bool ReadFile(const char *filename);
    bool ReadADCCalibData(const int runID);
    float GetCorrespondingCharge(uint16_t module_id, uint16_t pol_id, uint16_t ch_id, uint16_t adc_id) const;

private:
    void Init();
    int ConvertModuleID(uint16_t module_id) const;

    static const uint16_t n_modules = 10;
    static const uint16_t n_channels = 1024;
    static const uint16_t n_adc_channels = 32;

    float status[n_modules][2][n_channels][n_adc_channels];//2=num of pol
};

#endif // E16ANA_STSADCCALIBRATION_HH
