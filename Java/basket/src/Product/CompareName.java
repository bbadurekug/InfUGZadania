package Product;

import java.util.Comparator;

public class CompareName implements Comparator<Product>{
    @Override
    public int compare(Product x, Product y) {
        return x.getName().compareTo(y.getName());
    }
}