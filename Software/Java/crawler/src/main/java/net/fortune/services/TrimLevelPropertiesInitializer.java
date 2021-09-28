package net.fortune.services;

import net.fortune.entities.TrimLevel;

import java.util.HashMap;
import java.util.Map;

interface InitialiseFieldAction {
    void initialise(TrimLevel object, String value);
};


public class TrimLevelPropertiesInitializer {

    private static int FindFirstInteger(String content) {
        try {
            String[] stringParts = content.split(" ");
            // parse first parts of content as integer
            return Integer.parseInt(stringParts[0]);
        } catch (NumberFormatException e) {
            return 0;
        }
    }

    private static double FindFirstDouble(String content) {
        try {
            String[] stringParts = content.split(" ");
            // parse first parts of content as integer
            return Double.parseDouble(stringParts[0]);
        } catch (NumberFormatException e) {
            return 0.0;
        }
    }


    public static Map<String, InitialiseFieldAction> stringToSetterMapper = new HashMap<>() {{
        // BodySpec properties
        put("車身型式", TrimLevel::setBodyStyle);
        put("乘客數", (TrimLevel o, String value) -> { o.setSeats(FindFirstInteger(value));} );
        put("車長", (TrimLevel o, String value) -> { o.setLength(FindFirstInteger(value));} );
        put("車寬", (TrimLevel o, String value) -> { o.setWidth(FindFirstInteger(value));} );
        put("車高", (TrimLevel o, String value) -> { o.setHeight(FindFirstInteger(value));} );
        put("軸距", (TrimLevel o, String value) -> { o.setWheelbase(FindFirstInteger(value));} );
        put("車重", (TrimLevel o, String value) -> { o.setWeight(FindFirstInteger(value));} );
        put("行李容積", TrimLevel::setStandardCargoVolume);
        // PowerTrain properties
        put("燃料", TrimLevel::setPowerType);
        put("變速系統", TrimLevel::setTransmission);
        put("傳動方式", TrimLevel::setDriveWheel);
        // Engine properties
        put("排氣量", (TrimLevel o, String value) -> { o.setEngineDisplacement(Integer.parseInt(value.replace("c.c.", "").trim()));});
        put("引擎最大馬力", (TrimLevel o, String value) -> { o.setMaxHorsepower(FindFirstDouble(value));} );
        put("引擎最大扭力", (TrimLevel o, String value) -> { o.setMaxTorque(FindFirstDouble(value));} );
        put("市區油耗", (TrimLevel o, String value) -> { o.setCityFuelEfficiency(FindFirstDouble(value));} );
        put("高速油耗", (TrimLevel o, String value) -> { o.setFreewayFuelEfficiency(FindFirstDouble(value));} );
        put("平均油耗", (TrimLevel o, String value) -> { o.setAverageFuelEfficiency(FindFirstDouble(value));} );

        // Electric Motor properties
//        private double batteryCapacity;
//        private double motorTorque;
//        private double motorPower;
//        private double electricEfficiency;
//        private double electricRange;
//        private double cityRange;
//        private double freewayRange;
//        private double combinedRange;
//        private String chargingTime;
        // Safety properties
        put("ABS防止煞車鎖死系統", TrimLevel::setAntilockBrakingSystem);
        put("循跡控制系統", TrimLevel::setAccelerationStabilityRetainer);
        put("EBD煞車力分配系統", TrimLevel::setElectronicBrakeforceDistribution);
        put("煞車力道輔助系統", TrimLevel::setBrakeAssistSystem);
        put("ESC電子穩定控制系統", TrimLevel::setElectronicStabilityProgram);
        put("定速裝置", TrimLevel::setCruiseControl);
        put("車距維持巡航系統", TrimLevel::setAdaptiveCruiseControl);
        put("預警防護", TrimLevel::setForwardCollisionWarning);
        put("AEB自動緊急煞車", TrimLevel::setAutomaticEmergencyBraking);
        put("車道偏移", (TrimLevel o, String value) -> {
            o.setLaneDepartureWarning(value);
            o.setLaneDepartureRevise(value);
        });
        put("盲點偵測", TrimLevel::setBlindSpotWarning);
        put("ISOFIX兒童安全椅安裝系統", TrimLevel::setIsofix);
        put("自動停車", TrimLevel::setActiveParkingAssistance);
        put("倒車攝影系統", TrimLevel::setRearViewCamera);
        put("氣囊總數", (TrimLevel o, String value) -> {
            String newValue = value.replace("具", "").trim();
            o.setAirBagNumbers(newValue);
        });
//        rearCrossTrafficWarning = "";
//        reverseAutomaticEmergencyBraking = "";
//        hillStartAssis = "";
//        hillDescentControl = "";
//        iihsDescription = "";
//        ncapDescription = "";
//        surroundViewCamera = "";
    }};


    public static void SetTrimLevelPropertyValue(TrimLevel level, String propertyName, String value) {
        if (stringToSetterMapper.containsKey(propertyName)) {
            stringToSetterMapper.get(propertyName).initialise(level, value);
        }
    }
}
