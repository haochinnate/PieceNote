package net.fortune.entities;

public class Maker {
    public Maker() {}

    private String name;
    private String chineseName;
    private String url;
    private String level;
    private int id;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getChineseName() {
        return chineseName;
    }

    public void setChineseName(String chineseName) {
        this.chineseName = chineseName;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getLevel() {
        return level;
    }

    public void setLevel(String level) {
        this.level = level;
    }

    public int getId() { return id; }

    public void setId(int id) { this.id = id; }

    @Override
    public String toString() {
        return "Maker{" +
                "name='" + name + '\'' +
                ", chineseName='" + chineseName + '\'' +
                ", url='" + url + '\'' +
                ", level='" + level + '\'' +
                ", id=" + id +
                '}';
    }
}
