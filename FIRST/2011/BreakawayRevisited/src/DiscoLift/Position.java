/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DiscoLift;

import edu.wpi.first.wpilibj.*;
import Breakaway.HW;
import Utils.DiscoUtils;

class Position {
    private static class AbstractPosition {
        private static int m_value = 0;
        private static int m_encoderCount = 0;

        /**
         * Default construction for a position
         * @param value
         * @param encoderCount
         */
        protected AbstractPosition(int value, int encoderCount){
            m_value = value;
            m_encoderCount = encoderCount;
        }

        /**
         * Get the value for this position
         * @return
         */
        public static int getValue() {
            return m_value;
        }

        /**
         * get the encoder count for this position
         * @return
         */
        public static int getEncoderCount() {
            return m_encoderCount;
        }

        /**
         * This function tells you when a positions limit switch combination has been hit
         * @return
         */
        public static boolean isLimit() {
            DiscoUtils.debugPrintln("Did not overright isLimit: returned false");
            return false;
        }
    }

    public static class FullDown extends AbstractPosition {
        //Set Position value and encoderCount
        private FullDown(){super(0,0);}
        //LimitSwitch combination for this Position
        public static boolean isLimit() {
            return (HW.limit1.get() && !HW.limit2.get() && !HW.limit3.get());
        }
    }
    public static class Pos1 extends AbstractPosition {
        //Set Position value and encoderCount
        private Pos1(){super(1,100);}
        //LimitSwitch combination for this Position
        public static boolean isLimit() {
            return (!HW.limit1.get() && HW.limit2.get() && !HW.limit3.get());
        }
    }
    public static class Pos2 extends AbstractPosition {
        //Set Position value and encoderCount
        private Pos2(){super(2,140);}
        //LimitSwitch combination for this Position
        public static boolean isLimit() {
            return (HW.limit1.get() && HW.limit2.get() && !HW.limit3.get());
        }
    }

}