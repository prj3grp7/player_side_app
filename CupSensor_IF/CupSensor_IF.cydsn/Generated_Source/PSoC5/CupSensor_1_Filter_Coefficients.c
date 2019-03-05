#include "CupSensor_1_Filter.h"
#include "CupSensor_1_Filter_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is: Biquad
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelABiquadCoefficients CupSensor_1_Filter_ChannelABiquadCoefficients

/* Number of Biquad sections are: 3 */

const uint8 CYCODE CupSensor_1_Filter_ChannelABiquadCoefficients[CupSensor_1_Filter_BIQUAD_A_SIZE] = 
{
 /* Coefficients of Section 0 */
 0xE9u, 0x42u, 0x06u, 0x00u, /* Section(0)_A0, 0.0978338718414307 */

 0xD3u, 0x85u, 0x0Cu, 0x00u, /* Section(0)_A1, 0.19566798210144 */

 0xE9u, 0x42u, 0x06u, 0x00u, /* Section(0)_A2, 0.0978338718414307 */

 0xAAu, 0x59u, 0xE8u, 0x00u, /* Section(0)_B1, 0.369527339935303 */

 0xC1u, 0x77u, 0xF3u, 0x00u, /* Section(0)_B2, 0.195815801620483 */

 /* Coefficients of Section 1 */
 0x13u, 0xD5u, 0x15u, 0x00u, /* Section(1)_A0, 0.341130018234253 */

 0x26u, 0xAAu, 0x2Bu, 0x00u, /* Section(1)_A1, 0.682260036468506 */

 0x13u, 0xD5u, 0x15u, 0x00u, /* Section(1)_A2, 0.341130018234253 */

 0x66u, 0x62u, 0xEBu, 0x00u, /* Section(1)_B1, 0.322119235992432 */

 0x53u, 0x49u, 0xFDu, 0x00u, /* Section(1)_B2, 0.0423996448516846 */

 /* Coefficients of Section 2 */
 0x42u, 0x9Du, 0x21u, 0x00u, /* Section(2)_A0, 2.10089302062988 */

 0x84u, 0x3Au, 0x43u, 0x00u, /* Section(2)_A1, 4.20178604125977 */

 0x42u, 0x9Du, 0x21u, 0x00u, /* Section(2)_A2, 2.10089302062988 */

 0x4Au, 0x42u, 0xE0u, 0x00u, /* Section(2)_B1, 0.495954036712646 */

 0xA4u, 0x48u, 0xD9u, 0x00u, /* Section(2)_B2, 0.604941368103027 */
};

