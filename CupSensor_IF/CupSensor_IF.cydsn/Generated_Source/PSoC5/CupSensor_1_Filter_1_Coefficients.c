#include "``$INSTANCE_NAME`_Filter_1.h"
#include "``$INSTANCE_NAME`_Filter_1_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is: Biquad
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelABiquadCoefficients ``$INSTANCE_NAME`_Filter_1_ChannelABiquadCoefficients

/* Number of Biquad sections are: 1 */

const uint8 CYCODE ``$INSTANCE_NAME`_Filter_1_ChannelABiquadCoefficients[``$INSTANCE_NAME`_Filter_1_BIQUAD_A_SIZE] = 
{
 /* Coefficients of Section 0 */
 0xD3u, 0xF3u, 0x01u, 0x00u, /* Section(0)_A0, 0.0305068492889404 */

 0xD3u, 0xF3u, 0x01u, 0x00u, /* Section(0)_A1, 0.0305068492889404 */

 0x00u, 0x00u, 0x00u, 0x00u, /* Section(0)_A2, 0 */

 0x9Au, 0x19u, 0x3Cu, 0x00u, /* Section(0)_B1, -0.939062595367432 */

 0x00u, 0x00u, 0x00u, 0x00u, /* Section(0)_B2, 0 */
};

