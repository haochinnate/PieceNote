package net.fortune.entities;

public class CarModel {

    private String name = "";
    private String bodyStyle = "";
    private String officialUrl = "";
    private String isArchived = "";
    private String manufacturerId = "";
    private String alias = "";
    private String releaseDate = "";
    private String yearsInfo = "";
    private String mainImage = "";
    private int id;
    private String url = "";
    private String specUrl = "";
    private String equipUrl = "";

    public CarModel() {
    }

    public CarModel(String name, String manufacturerId, String url) {
        this.name = name;
        this.manufacturerId = manufacturerId;
        this.url = url;
        this.specUrl = url.replace("overall", "spec");
        this.equipUrl = url.replace("overall", "equip");
    }

    @Override
    public String toString() {
        return "CarModel{" +
                "name='" + name + '\'' +
                ", manufacturerId='" + manufacturerId + '\'' +
                ", url='" + url + '\'' +
                ", specUrl='" + specUrl + '\'' +
                ", equipUrl='" + equipUrl + '\'' +
                '}';
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getBodyStyle() {
        return bodyStyle;
    }

    public void setBodyStyle(String bodyStyle) {
        this.bodyStyle = bodyStyle;
    }

    public String getOfficialUrl() {
        return officialUrl;
    }

    public void setOfficialUrl(String officialUrl) {
        this.officialUrl = officialUrl;
    }

    public String getIsArchived() {
        return isArchived;
    }

    public void setIsArchived(String isArchived) {
        this.isArchived = isArchived;
    }

    public String getManufacturerId() {
        return manufacturerId;
    }

    public void setManufacturerId(String manufacturerId) {
        this.manufacturerId = manufacturerId;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }

    public String getReleaseDate() {
        return releaseDate;
    }

    public void setReleaseDate(String releaseDate) {
        this.releaseDate = releaseDate;
    }

    public String getYearsInfo() {
        return yearsInfo;
    }

    public void setYearsInfo(String yearsInfo) {
        this.yearsInfo = yearsInfo;
    }

    public String getMainImage() {
        return mainImage;
    }

    public void setMainImage(String mainImage) {
        this.mainImage = mainImage;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getSpecUrl() {
        return specUrl;
    }

    public void setSpecUrl(String specUrl) {
        this.specUrl = specUrl;
    }

    public String getEquipUrl() {
        return equipUrl;
    }

    public void setEquipUrl(String equipUrl) {
        this.equipUrl = equipUrl;
    }


//    self.name = name
//    self.manufacturer = manufacturer
//    self.url = url
//    self. = replace_last(url, 'overall', 'spec')
//    self. = replace_last(url, 'overall', 'equip')

//
}
