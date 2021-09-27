package net.fortune;

import net.fortune.entities.CarModel;
import net.fortune.entities.Maker;
import net.fortune.entities.TrimLevel;
import net.fortune.services.TrimLevelPropertiesInitializer;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class UcarWebProcessor {

    private static String _modelDiv_className = "div.cell_topic_new_r";
    private static String _modelUrlPrefix = "https://newcar.u-car.com.tw";
    private static String _levelTable_ClassName = "table.table_compare";

    public static List<CarModel> getModelsOf(Maker maker) throws IOException {
        List<CarModel> carModels = new ArrayList<>();

        Document doc = Jsoup.connect(maker.getUrl()).get();
//        String title = doc.title();
//        System.out.println(title);

        Elements modelsDivs = doc.select(_modelDiv_className);

        for (Element modelDiv : modelsDivs) {

            Element title = modelDiv.selectFirst("p.title");

            String modelTitle = title.text();

            String modelUrl = title.parent().attr("href");

            CarModel carModel = new CarModel(modelTitle, maker.getName(), _modelUrlPrefix + modelUrl);

            carModels.add(carModel);
        }

        return carModels;
    }

    public static List<TrimLevel> getLevelsOf(CarModel model) throws IOException {
        List<TrimLevel> levels = new ArrayList<>();

        Document specDoc = Jsoup.connect(model.getSpecUrl()).get();
        Document equipDoc = Jsoup.connect(model.getEquipUrl()).get();

        Element specTable = specDoc.selectFirst(_levelTable_ClassName);
        Element equipTable = equipDoc.selectFirst(_levelTable_ClassName);

        Elements levelsTitles = specTable.select("td.title_block");
        int numberOfLevels = levelsTitles.size() - 1; // -1 for the name column in the table
        for (int i = 0; i < numberOfLevels; i++) {
            TrimLevel tmpLevel = new TrimLevel();
            tmpLevel.setManufacturerId(model.getManufacturerId());
            tmpLevel.setCarmodelId(model.getName());
            levels.add(tmpLevel);
        }

        // get the level name and price
        Element specHeadRow = specTable.selectFirst("thead").selectFirst("tr");
        setNameAndPriceOfLevels(levels, specHeadRow);

        Element specTbody = specTable.selectFirst("tbody");
        Elements specRows = specTbody.select("tr");

        for (int rowIdx = 0; rowIdx < specRows.size(); rowIdx++) {

            Element row = specRows.get(rowIdx);
            // this row is not item, so skip
            if (row.selectFirst("td.list") == null) {
                continue;
            }

            String itemName = row.selectFirst("td.list").text();
            System.out.println(itemName);

            Elements cells = row.select("td");

            for (int cellIdx = 1; cellIdx < cells.size(); cellIdx++) {
                Element cell = cells.get(cellIdx);

                if (cell.className().equals("same")) {
                    int colSpan = Integer.parseInt(cell.attr("colspan"));

                    String cellText = cell.text();
                    if(cellText == null || cellText.equals("") || cellText.trim().equals(""))
                    {
                        continue;
                    }
                    for (int i = 0; i < colSpan; i++) {
                        TrimLevelPropertiesInitializer.SetTrimLevelPropertyValue(levels.get(i), itemName, cell.text());
                    }
                }

                if (cell.className().equals("different")) {
//                    System.out.println(cell.text());
                    String cellText = cell.text();
                    if(cellText == null || cellText.equals("") || cellText.trim().equals(""))
                    {
                        continue;
                    }
                    TrimLevelPropertiesInitializer.SetTrimLevelPropertyValue(levels.get(cellIdx -1), itemName, cell.text());
                }
            }

        }

        // handle Equip table
        Element equipTbody = equipTable.selectFirst("tbody");
        Elements equipRows = equipTbody.select("tr");
        for (int rowIdx = 0; rowIdx < equipRows.size(); rowIdx++) {
            Element row = equipRows.get(rowIdx);

            // this row is not equip item, so skip
            if (row.selectFirst("td.list") == null) {
                continue;
            }

            String itemName = row.selectFirst("td.list").text();
            if (!TrimLevelPropertiesInitializer.stringToSetterMapper.containsKey(itemName)) {
                continue;
            }
            System.out.println(itemName);

            Elements cells = row.select("td");

            for (int cellIdx = 1; cellIdx < cells.size(); cellIdx++) {
                Element cell = cells.get(cellIdx);

                System.out.println(cell.text());
                String cellText = cell.text();
//                if(cellText == null || cellText.equals("") || cellText.trim().equals("")) {
//                    continue;
//                }
                String equipStatus = "";
                Element equipStatusImg = cell.selectFirst("img");
                if (equipStatusImg == null) {
                    equipStatus = "Unknown()";
                }
                else {
                    String equipStatusImgSrc = cell.selectFirst("img").attr("src");
                    if (equipStatusImgSrc.contains("round.png")) {
                        equipStatus = "S(" + cellText.trim() + ")";
                    }
                    else if (equipStatusImgSrc.contains("non.png")) {
                        equipStatus = "N()";
                    }
                    else if (equipStatusImgSrc.contains("selected")) {
                        equipStatus = "O(" + cellText.trim() + ")";
                    }
                }

                TrimLevelPropertiesInitializer.SetTrimLevelPropertyValue(levels.get(cellIdx -1), itemName, equipStatus);
            }
        }


        return levels;
    }

    private static void setNameAndPriceOfLevels(List<TrimLevel> levels, Element headerRow) {
        Elements cells = headerRow.select("td");

        for (int cellIdx = 0; cellIdx < cells.size(); cellIdx++) {
            Element cell = cells.get(cellIdx);
//                System.out.println(cell);

            // cellIdx 0 is name of that row
            if (cell.className().equals("title_block") && cellIdx > 0) {
//                    System.out.println(cell);
                Elements ps = cell.select("p");
                for (Element p : ps) {
                    if (p.className().equals("text_type")) {
//                        System.out.println(p.text());
                        levels.get(cellIdx - 1).setName(p.text());
                    } else if (p.className().equals("text_number")) {
//                        System.out.println(p.selectFirst("strong").text());
                        levels.get(cellIdx - 1).setPrice(p.selectFirst("strong").text());
                    }
                }
            }
        }
    }
}
