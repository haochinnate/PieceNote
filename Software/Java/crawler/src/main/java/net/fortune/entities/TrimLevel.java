package net.fortune.entities;

import java.io.FileWriter;
import java.io.IOException;

public class TrimLevel {

    public TrimLevel() {
    }

    // Basic properties
    private int id;
    private String name;
    private String price;
    private boolean isArchived;
    private int manufacturerId = 0;
    private int carmodelId = 0;
    // BodySpec properties
    private String bodyStyle = "";
    private int seats;
    private int length;
    private int width;
    private int height;
    private int wheelbase;
    private int weight;
    private String standardCargoVolume; // store the whole volume in this property
    private int fiveSeatsCargoVolume;
    private int maxCargoVolume;
    private int frunkCargoVolume;
    // PowerTrain properties
    private String powerType = "";
    private String transmission = "";
    private String driveWheel = "";
    // Engine properties
    private int engineDisplacement;
    private double maxTorque;
    private double maxHorsepower;
    private double cityFuelEfficiency;
    private double freewayFuelEfficiency;
    private double averageFuelEfficiency;
    // Electric Motor properties
    private double batteryCapacity;
    private double motorTorque;
    private double motorPower;
    private double electricEfficiency;
    private double electricRange;
    private double cityRange;
    private double freewayRange;
    private double combinedRange;
    private String chargingTime = "";
    // Safety properties
    private String antilockBrakingSystem = "";
    private String accelerationStabilityRetainer = "";
    private String electronicBrakeforceDistribution = "";
    private String brakeAssistSystem = "";
    private String electronicStabilityProgram = "";
    private String cruiseControl = "";
    private String adaptiveCruiseControl = "";
    private String forwardCollisionWarning = "";
    private String automaticEmergencyBraking = "";
    private String laneDepartureWarning = "";
    private String laneDepartureRevise = "";
    private String laneKeepingAssistance = "";
    private String rearCrossTrafficWarning = "";
    private String blindSpotWarning = "";
    private String reverseAutomaticEmergencyBraking = "";
    private String hillStartAssis = "";
    private String hillDescentControl = "";
    private String airBagNumbers = "";
    private String isofix = "";
    private String activeParkingAssistance = "";
    private String iihsDescription = "";
    private String ncapDescription = "";
    private String surroundViewCamera = "";
    private String rearViewCamera = "";

    public void printSqlInsertStatement() {
        try {
            String insertTrimLevelStatement = getInsertTrimLevelStatement();
            String insertBodySpecStatement = getInsertBodySpecStatement();
            String insertElectricMotorSpecStatement = getInsertElectricMotorSpecStatement();
            String insertEngineSpecStatement = getInsertEngineSpecStatement();
            String insertPowerTrainStatement = getInsertPowerTrainStatement();
            String insertSafetyEquipmentStatement = getInsertSafetyEquipmentStatement();
            String insertCarModelBodyStyleStatement = getInsertCarModelBodyStyleStatement();

            FileWriter myWriter = new FileWriter("D:\\\\cartrimlevels_seed.sql", true);
            myWriter.write(insertTrimLevelStatement + System.lineSeparator());
            myWriter.write(insertBodySpecStatement + System.lineSeparator());
            myWriter.write(insertElectricMotorSpecStatement + System.lineSeparator());
            myWriter.write(insertEngineSpecStatement + System.lineSeparator());
            myWriter.write(insertPowerTrainStatement + System.lineSeparator());
            myWriter.write(insertSafetyEquipmentStatement + System.lineSeparator());
            myWriter.write(insertCarModelBodyStyleStatement + System.lineSeparator());
            myWriter.write(System.lineSeparator());
            myWriter.close();
//            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    private String getInsertCarModelBodyStyleStatement() {
        String insertStatement = String.format("insert into carmodelbodystyles(CarModelId, BodyStyleId) " +
                "values (%d, BBODYSTYLE %s);", carmodelId, bodyStyle);

        return insertStatement;
    }

    private String getInsertSafetyEquipmentStatement() {
        String insertStatement = String.format("insert into safetyequipment(Id, CarTrimLevelId, AntilockBrakingSystem, " +
                        "AccelerationStabilityRetainer, ElectronicBrakeforceDistribution, BrakeAssistSystem, ElectronicStabilityProgram, " +
                        "CruiseControl, AdaptiveCruiseControl, ForwardCollisionWarning, AutomaticEmergencyBraking, LaneDepartureWarning, " +
                        "LaneDepartureRevise, LaneKeepingAssistance, RearCrossTrafficWarning, BlindSpotWarning, " +
                        "ReverseAutomaticEmergencyBraking, HillStartAssis, HillDescentControl, AirBagNumbers, Isofix, " +
                        "ActiveParkingAssistance, IihsDescription, NcapDescription, SurroundViewCamera, RearViewCamera) " +
                        "values (%d, %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", LLANE \"%s\", " +
                        "  \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", AAIR \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");",
                id, id, antilockBrakingSystem, accelerationStabilityRetainer, electronicBrakeforceDistribution, brakeAssistSystem,
                electronicStabilityProgram, cruiseControl, adaptiveCruiseControl, forwardCollisionWarning, automaticEmergencyBraking, laneDepartureWarning,
                laneDepartureRevise, laneKeepingAssistance, rearCrossTrafficWarning, blindSpotWarning, reverseAutomaticEmergencyBraking,
                hillStartAssis, hillDescentControl, airBagNumbers, isofix, activeParkingAssistance, iihsDescription, ncapDescription,
                surroundViewCamera, rearViewCamera);

        return insertStatement;
    }

    private String getInsertPowerTrainStatement() {
        String insertStatement = String.format("insert into powertrains(Id, CarTrimLevelId, PowerTypeId, Transmission, Drivewheel) " +
                "values (%d, %d, PPOWERTYPE %s, \"%s\", \"%s\");", id, id, powerType, transmission, driveWheel);

        return insertStatement;
    }

    //        String insertStatement = String.format( "insert into carmodels(Id, Name, IsArchived, YearsInfo, CarMakerId, ReleaseDate) "
//                + "values (%d, \"%s\", b\'0\', \"2022年式\", %d, \"2022-01-01\");%s", id, name, manufacturerId, System.lineSeparator());
////            System.out.println(insertStatement);

    private String getInsertEngineSpecStatement() {
        String insertStatement = String.format("insert into enginespecs(Id, CarTrimLevelId, EngineDisplacement, MaxTorque, " +
                "MaxHorsepower, CityFuelEfficiency, FreewayFuelEfficiency, AverageFuelEfficiency) " +
                "values (%d, %d, %d, %f, %f, %f, %f, %f);",
                id, id, engineDisplacement, maxTorque, maxHorsepower, cityFuelEfficiency, freewayFuelEfficiency, averageFuelEfficiency);

        return insertStatement;
    }

    private String getInsertElectricMotorSpecStatement() {
        String insertStatement = String.format("insert into electricmotorspecs(Id, CarTrimLevelId, BatteryCapacity, " +
                "MotorTorque, MotorPower, ElectricEfficiency, ElectricRange, FreewayRange, CityRange, CombinedRange, " +
                "ChargingTime, RangeNEDC, RangeWLTP, RangeEPA) " +
                "values(%d, %d, %f, %f, %f, %f, %f, %f, %f, %f, \"%s\", %f, %f, %f);",
                id, id, batteryCapacity, motorTorque, motorPower, electricEfficiency, electricRange, freewayRange, cityRange,
                combinedRange, chargingTime, electricRange, electricRange, electricRange);

        return insertStatement;
    }

    private String getInsertBodySpecStatement() {
        //    insert into bodyspecs(Id, CarTrimLevelId, Seats, Length, Width, Height, WheelBase, Weight,
        //        StandardCargoVolume, FiveSeatsCargoVolume, MaxCargoVolume, FrunkCargoVolume)
        //        values(77, 77, 5, 4000, 2000, 4000, 2000, 2000, 200, 300, 100, 400);

        String insertStatement = String.format("insert into bodyspecs(Id, CarTrimLevelId, Seats, Length, Width, " +
                "Height, WheelBase, Weight, StandardCargoVolume, FiveSeatsCargoVolume, MaxCargoVolume, FrunkCargoVolume) "
                + "values (%d, %d, %d, %d, %d, %d, %d, %d, SSTANDARD%s, %d, %d, %d);",
                id, id, seats, length, width, height, wheelbase, weight,
                standardCargoVolume, fiveSeatsCargoVolume, maxCargoVolume, frunkCargoVolume);
        return insertStatement;
    }

    private String getInsertTrimLevelStatement() {
        // insert into cartrimlevels(Id, Name, IsArchived, Price, CarModelId) values (88, "Style", b'1', 980000, 3);

        String insertStatement = String.format("insert into cartrimlevels(Id, Name, IsArchived, Price, CarModelId) "
            + "values (%d, \"%s\", b\'0\', PPRICE: %s, %d);", id, name, price, carmodelId);

        return insertStatement;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPrice() {
        return price;
    }

    public void setPrice(String price) {
        this.price = price;
    }

    public boolean isArchived() {
        return isArchived;
    }

    public void setArchived(boolean archived) {
        isArchived = archived;
    }

    public int getManufacturerId() { return manufacturerId; }

    public void setManufacturerId(int manufacturerId) {
        this.manufacturerId = manufacturerId;
    }

    public int getCarmodelId() {
        return carmodelId;
    }

    public void setCarmodelId(int carmodelId) {
        this.carmodelId = carmodelId;
    }

    public String getBodyStyle() {
        return bodyStyle;
    }

    public void setBodyStyle(String bodyStyle) {
        this.bodyStyle = bodyStyle;
    }

    public int getSeats() {
        return seats;
    }

    public void setSeats(int seats) {
        this.seats = seats;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getWheelbase() {
        return wheelbase;
    }

    public void setWheelbase(int wheelbase) {
        this.wheelbase = wheelbase;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public String getStandardCargoVolume() {
        return standardCargoVolume;
    }

    public void setStandardCargoVolume(String standardCargoVolume) {
        this.standardCargoVolume = standardCargoVolume;
    }

    public int getFiveSeatsCargoVolume() {
        return fiveSeatsCargoVolume;
    }

    public void setFiveSeatsCargoVolume(int fiveSeatsCargoVolume) {
        this.fiveSeatsCargoVolume = fiveSeatsCargoVolume;
    }

    public int getMaxCargoVolume() {
        return maxCargoVolume;
    }

    public void setMaxCargoVolume(int maxCargoVolume) {
        this.maxCargoVolume = maxCargoVolume;
    }

    public int getFrunkCargoVolume() {
        return frunkCargoVolume;
    }

    public void setFrunkCargoVolume(int frunkCargoVolume) {
        this.frunkCargoVolume = frunkCargoVolume;
    }

    public String getPowerType() {
        return powerType;
    }

    public void setPowerType(String powerType) {
        this.powerType = powerType;
    }

    public String getTransmission() {
        return transmission;
    }

    public void setTransmission(String transmission) {
        this.transmission = transmission;
    }

    public String getDriveWheel() {
        return driveWheel;
    }

    public void setDriveWheel(String driveWheel) {
        this.driveWheel = driveWheel;
    }

    public int getEngineDisplacement() {
        return engineDisplacement;
    }

    public void setEngineDisplacement(int engineDisplacement) {
        this.engineDisplacement = engineDisplacement;
    }

    public double getMaxTorque() {
        return maxTorque;
    }

    public void setMaxTorque(double maxTorque) {
        this.maxTorque = maxTorque;
    }

    public double getMaxHorsepower() {
        return maxHorsepower;
    }

    public void setMaxHorsepower(double maxHorsepower) {
        this.maxHorsepower = maxHorsepower;
    }

    public double getCityFuelEfficiency() {
        return cityFuelEfficiency;
    }

    public void setCityFuelEfficiency(double cityFuelEfficiency) {
        this.cityFuelEfficiency = cityFuelEfficiency;
    }

    public double getFreewayFuelEfficiency() {
        return freewayFuelEfficiency;
    }

    public void setFreewayFuelEfficiency(double freewayFuelEfficiency) {
        this.freewayFuelEfficiency = freewayFuelEfficiency;
    }

    public double getAverageFuelEfficiency() {
        return averageFuelEfficiency;
    }

    public void setAverageFuelEfficiency(double averageFuelEfficiency) {
        this.averageFuelEfficiency = averageFuelEfficiency;
    }

    public double getBatteryCapacity() {
        return batteryCapacity;
    }

    public void setBatteryCapacity(double batteryCapacity) {
        this.batteryCapacity = batteryCapacity;
    }

    public double getMotorTorque() {
        return motorTorque;
    }

    public void setMotorTorque(double motorTorque) {
        this.motorTorque = motorTorque;
    }

    public double getMotorPower() {
        return motorPower;
    }

    public void setMotorPower(double motorPower) {
        this.motorPower = motorPower;
    }

    public double getElectricEfficiency() {
        return electricEfficiency;
    }

    public void setElectricEfficiency(double electricEfficiency) {
        this.electricEfficiency = electricEfficiency;
    }

    public double getElectricRange() {
        return electricRange;
    }

    public void setElectricRange(double electricRange) {
        this.electricRange = electricRange;
    }

    public double getCityRange() {
        return cityRange;
    }

    public void setCityRange(double cityRange) {
        this.cityRange = cityRange;
    }

    public double getFreewayRange() {
        return freewayRange;
    }

    public void setFreewayRange(double freewayRange) {
        this.freewayRange = freewayRange;
    }

    public double getCombinedRange() {
        return combinedRange;
    }

    public void setCombinedRange(double combinedRange) {
        this.combinedRange = combinedRange;
    }

    public String getChargingTime() {
        return chargingTime;
    }

    public void setChargingTime(String chargingTime) {
        this.chargingTime = chargingTime;
    }

    public String getAntilockBrakingSystem() {
        return antilockBrakingSystem;
    }

    public void setAntilockBrakingSystem(String antilockBrakingSystem) {
        this.antilockBrakingSystem = antilockBrakingSystem;
    }

    public String getAccelerationStabilityRetainer() {
        return accelerationStabilityRetainer;
    }

    public void setAccelerationStabilityRetainer(String accelerationStabilityRetainer) {
        this.accelerationStabilityRetainer = accelerationStabilityRetainer;
    }

    public String getElectronicBrakeforceDistribution() {
        return electronicBrakeforceDistribution;
    }

    public void setElectronicBrakeforceDistribution(String electronicBrakeforceDistribution) {
        this.electronicBrakeforceDistribution = electronicBrakeforceDistribution;
    }

    public String getBrakeAssistSystem() {
        return brakeAssistSystem;
    }

    public void setBrakeAssistSystem(String brakeAssistSystem) {
        this.brakeAssistSystem = brakeAssistSystem;
    }

    public String getElectronicStabilityProgram() {
        return electronicStabilityProgram;
    }

    public void setElectronicStabilityProgram(String electronicStabilityProgram) {
        this.electronicStabilityProgram = electronicStabilityProgram;
    }

    public String getCruiseControl() {
        return cruiseControl;
    }

    public void setCruiseControl(String cruiseControl) {
        this.cruiseControl = cruiseControl;
    }

    public String getAdaptiveCruiseControl() {
        return adaptiveCruiseControl;
    }

    public void setAdaptiveCruiseControl(String adaptiveCruiseControl) {
        this.adaptiveCruiseControl = adaptiveCruiseControl;
    }

    public String getForwardCollisionWarning() {
        return forwardCollisionWarning;
    }

    public void setForwardCollisionWarning(String forwardCollisionWarning) {
        this.forwardCollisionWarning = forwardCollisionWarning;
    }

    public String getAutomaticEmergencyBraking() {
        return automaticEmergencyBraking;
    }

    public void setAutomaticEmergencyBraking(String automaticEmergencyBraking) {
        this.automaticEmergencyBraking = automaticEmergencyBraking;
    }

    public String getLaneDepartureWarning() {
        return laneDepartureWarning;
    }

    public void setLaneDepartureWarning(String laneDepartureWarning) {
        this.laneDepartureWarning = laneDepartureWarning;
    }

    public String getLaneDepartureRevise() {
        return laneDepartureRevise;
    }

    public void setLaneDepartureRevise(String laneDepartureRevise) {
        this.laneDepartureRevise = laneDepartureRevise;
    }

    public String getLaneKeepingAssistance() {
        return laneKeepingAssistance;
    }

    public void setLaneKeepingAssistance(String laneKeepingAssistance) {
        this.laneKeepingAssistance = laneKeepingAssistance;
    }

    public String getRearCrossTrafficWarning() {
        return rearCrossTrafficWarning;
    }

    public void setRearCrossTrafficWarning(String rearCrossTrafficWarning) {
        this.rearCrossTrafficWarning = rearCrossTrafficWarning;
    }

    public String getBlindSpotWarning() {
        return blindSpotWarning;
    }

    public void setBlindSpotWarning(String blindSpotWarning) {
        this.blindSpotWarning = blindSpotWarning;
    }

    public String getReverseAutomaticEmergencyBraking() {
        return reverseAutomaticEmergencyBraking;
    }

    public void setReverseAutomaticEmergencyBraking(String reverseAutomaticEmergencyBraking) {
        this.reverseAutomaticEmergencyBraking = reverseAutomaticEmergencyBraking;
    }

    public String getHillStartAssis() {
        return hillStartAssis;
    }

    public void setHillStartAssis(String hillStartAssis) {
        this.hillStartAssis = hillStartAssis;
    }

    public String getHillDescentControl() {
        return hillDescentControl;
    }

    public void setHillDescentControl(String hillDescentControl) {
        this.hillDescentControl = hillDescentControl;
    }

    public String getAirBagNumbers() {
        return airBagNumbers;
    }

    public void setAirBagNumbers(String airBagNumbers) {
        this.airBagNumbers = airBagNumbers;
    }

    public String getIsofix() {
        return isofix;
    }

    public void setIsofix(String isofix) {
        this.isofix = isofix;
    }

    public String getActiveParkingAssistance() {
        return activeParkingAssistance;
    }

    public void setActiveParkingAssistance(String activeParkingAssistance) {
        this.activeParkingAssistance = activeParkingAssistance;
    }

    public String getIihsDescription() {
        return iihsDescription;
    }

    public void setIihsDescription(String iihsDescription) {
        this.iihsDescription = iihsDescription;
    }

    public String getNcapDescription() {
        return ncapDescription;
    }

    public void setNcapDescription(String ncapDescription) {
        this.ncapDescription = ncapDescription;
    }

    public String getSurroundViewCamera() {
        return surroundViewCamera;
    }

    public void setSurroundViewCamera(String surroundViewCamera) {
        this.surroundViewCamera = surroundViewCamera;
    }

    public String getRearViewCamera() {
        return rearViewCamera;
    }

    public void setRearViewCamera(String rearViewCamera) {
        this.rearViewCamera = rearViewCamera;
    }
}
