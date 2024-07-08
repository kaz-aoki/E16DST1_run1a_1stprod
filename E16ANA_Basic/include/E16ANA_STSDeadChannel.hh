/*// E16ANA_STSDeadChannel.hh
// Created by R.Yamada
// Last modified at <2024-06-26 20:33:31>

#ifndef E16ANA_STSDEADCHANNEL_HH
#define E16ANA_STSDEADCHANNEL_HH

#include <string>
#include <vector>
#include <cstdint>

class E16ANA_STSDeadChannel {
public:
    E16ANA_STSDeadChannel();
    ~E16ANA_STSDeadChannel();

    bool ReadFile(const char *filename);
    bool ReadDeadChannelData(const int runID);
    bool IsOK(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsDead(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsNoisy(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsHot(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;

private:
    static const uint16_t n_modules = 10; // num of module
    static const uint16_t n_channels = 1024;

    int ConvertModuleID(uint16_t module_id) const;
    void Init();

    int status[n_modules][2][n_channels];
};

#endif // E16ANA_STSDEADCHANNEL_HH

//E16ANA_STSDeadChannel.hh 240626 by R.Yamada
//    Last modified at <2024-06-26 20:33:31 >
/*/

#ifndef E16ANA_STSDEADCHANNEL_HH
#define E16ANA_STSDEADCHANNEL_HH

#include <string>
#include <vector>
#include <cstdint>

class E16ANA_STSDeadChannel {
public:
    E16ANA_STSDeadChannel();
    ~E16ANA_STSDeadChannel();

    bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
    bool ReadConstantData(int run_id);
    bool ReadConstantDataByLocal(int run_id, std::string index_file_name);

    bool IsOK(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsDead(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsNoisy(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;
    bool IsHot(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const;

private:
    void Init();
    int ConvertModuleID(uint16_t module_id) const;

    static constexpr uint16_t n_modules = 10;  // num of module
    static constexpr uint16_t n_channels = 1024;

    int run_id;
    int status[n_modules][2][n_channels];
};

#endif // E16ANA_STSDEADCHANNEL_HH
