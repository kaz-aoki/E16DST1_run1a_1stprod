#ifndef E16DST_CONSTANT_HH
#define E16DST_CONSTANT_HH

namespace E16DST_Constant {

const int DST0HeaderSize = 1024 * 1024;

const int NSamplesSSD = 8;
const int NSamplesGTR = 15;
const int NSamplesHBD = 15;
// const int NSamplesLG = 2048;
const int NSamplesLG = 200;
const int NSamplesCT = 200;

const int NModules = 8;

const int NStripsSSD = 128 * 6;
const int NHitsMaxSSD = NStripsSSD * NModules;

const int NStripsGTR100 = 288 + 72 + 72;
const int NStripsGTR200 = 288 * 2 + 72 * 2;
const int NStripsGTR300 = 288 * 3 + 72 * 3;
const int NHitsMaxGTR = (NStripsGTR100 + NStripsGTR200 + NStripsGTR300) * NModules;

const int NPadsHBD = 1400;
const int NHitsMaxHBD = NPadsHBD * NModules;

const int NBlocksLG = 38;
const int NHitsMaxLG = NBlocksLG * NModules;

const int NTriggerChannelsGTR = 24; // per module
const int NTriggerChannelsHBD = 36; // per module
const int NTriggerChannelsLG = 38;  // per module

const int NTracksMaxUT3 = 128;
const int NNIMFlagsUT3 = 12; // uint8_t * 12 Byte (= 4n Byte)
const int NNIMScalersUT3 = 25;
const int NMergers = 5;
const int NMergerChannels = 256;

const int NTriggerTypes = 5;
const int NPhysicsTriggerTypes = 6;

enum Detector {
   GTR,
   HBD,
   LG,
};

const int TrackSrc = LG;

}; // namespace E16DST_Constant

#endif // E16DST_CONSTANT_HH
