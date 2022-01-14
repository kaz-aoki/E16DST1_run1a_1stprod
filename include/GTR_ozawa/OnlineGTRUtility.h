#ifndef OnlineGTRUtility_h
#define OnlineGTRUtility_h

#include <cstdint>
#include <map>
#include <unordered_map>

namespace OnlineGTR {
union IDs {
   uint64_t value64;
   struct {
      uint32_t strip_id;
      uint16_t layer_id;
      uint16_t module_id;
   };
   IDs(uint16_t _module_id, uint16_t _layer_id, uint32_t _strip_id)
      : strip_id(_strip_id), layer_id(_layer_id), module_id(_module_id){};
   IDs(uint16_t _module_id, uint16_t _layer_id) : strip_id(0xffffffff), layer_id(_layer_id), module_id(_module_id){};
   IDs(uint16_t _module_id) : strip_id(0xffffffff), layer_id(0xffff), module_id(_module_id){};
   ~IDs(){};
#if 0
   inline bool operator < (const IDs &rhs) const {
      return this->value64 < rhs.value64;
   };
   inline bool operator == (const IDs &rhs) const {
      return this->value64 == rhs.value64;
   };
   inline bool operator != (const IDs &rhs) const {
      return this->value64 != rhs.value64;
   };
#endif
};

template <class T>
using Map = std::map<uint64_t, T>;

template <class T>
using HashMap = std::unordered_map<uint64_t, T>;

// Don't use this, please update E16ANA
inline int KawamaToE16DST(int module_id_kawama)
{
   constexpr int module_id_e16dst[33] = {10, 110, 210, 9, 109, 209, 8, 108, 208, 7, 107, 207, 6, 106, 206, 5, 105, 205,
                                         4,  104, 204, 3, 103, 203, 2, 102, 202, 1, 101, 201, 0, 100, 200};
   return module_id_e16dst[module_id_kawama];
}

inline int E16DSTToKawama(int module_id_e16dst)
{
   constexpr int module_id_kawama[3][11] = {{30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0},
                                            {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                            {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}};
   return module_id_kawama[module_id_e16dst / 100][module_id_e16dst % 100];
}

}; // namespace OnlineGTR

#endif // OnlineGTRUtility_h
