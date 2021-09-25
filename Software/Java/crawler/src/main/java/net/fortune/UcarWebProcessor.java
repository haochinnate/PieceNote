package net.fortune;

import net.fortune.entities.CarModel;
import net.fortune.entities.Maker;
import net.fortune.entities.TrimLevel;
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

        Elements specTable = specDoc.select(_levelTable_ClassName);
        Elements equipTable = equipDoc.select(_levelTable_ClassName);

        Elements levelsTitles = specTable.select("td.title_block");
        int numberOfLevels = levelsTitles.size() - 1; // -1 for the name column in the table
        for (int i = 0; i < numberOfLevels; i++) {
            levels.add(new TrimLevel());
        }




//        for table_row in spec_table.findAll('tr'):
//        row_data = []
//        model_data = []
//        price_data = []
//        for idx, column in enumerate(table_row.findAll('td')):
//                # class="title_block"
//        if "title_block" in column.attrs['class'] and idx == 0:
//        row_data.append(column.text)
//        model_data.append("Model")
//        price_data.append("Price")
//        elif "title_block" in column.attrs['class']:
//        for p in column.findAll('p'):
//        if 'text_type' in p.attrs['class']:
//        row_data.append(p.text)
//        elif 'text_number' in p.attrs['class']:
//        price = p.find('strong').text
//        price_data.append(price)
//                        # print(p.text)
//        model_data.append(model_name)
//                        # print(column, flush=True)
//                    # print(column.text + ',', flush=True)
//
//                # class="list" (is spec or equip name)
//        if "list" in column.attrs['class'] and idx == 0:
//        row_data.append(column.text)
//
//        if "same" in column.attrs['class']:
//        row_data.extend([column.text] * int(column.attrs['colspan']))
//
//        if "different" in column.attrs['class']:
//        row_data.append(column.text)
//
//            # the row had process completed
//        if len(model_data) != 0:
//        levels_table.append(model_data)
//
//        if len(row_data) != 0:
//        levels_table.append(row_data)
//
//        if len(price_data) != 0:
//        levels_table.append(price_data)
//
//        for table_row in equip_table.findAll('tr'):
//        row_data = []
//
//        if 'class' in table_row.attrs:
//        if "sameequip" in table_row.attrs['class'] or "differentequip" in table_row.attrs['class']:
//
//        for idx, column in enumerate(table_row.findAll('td')):
//                        # the cell of equip name
//        if 'class' in column.attrs:
//        if "list" in column.attrs['class'] and idx == 0:
//        row_data.append(column.text)
//                        # the equip cell didn't have any content (blank content)
//        elif column.find('img'):
//        img = column.find('img')
//        if "round.png" in img.attrs['src']:   # "/images/ic_check_round.png"
//        row_data.append("S" + "(" + img.next.strip() + ")")
//        elif "non.png" in img.attrs['src']:   # "/images/ic_16_check_non.png"
//        row_data.append("N")
//        elif "selected" in img.attrs['src']:
//        row_data.append("O" + "(" + img.next.strip() + ")")
//        elif not column.text.strip():
//        row_data.append("N")
//        elif column.text.strip():
//        row_data.append(column.text.strip())
//
//        if len(row_data) != 0:
//        levels_table.append(row_data)
//
//        # rotate the table content
//        levels_table = [list(i) for i in zip(*levels_table)]
//
//        # levels_table[0] is equipment/spec name, the value is start from 0
//        # equipment/spec name set as key in dictionary
//        levels = []
//        for level in levels_table[1:]:
//        trim_level_object = TrimLevel(level[1], '', model_name)
//        trim_level_object.data = dict(zip(levels_table[0], level))
//        levels.append(trim_level_object)
//
//        # for each level in levels, formatting the value and change the name of equipment/spec


        return levels;
    }
}
