package Product;

import java.util.Comparator;

public class ComparePrice implements Comparator<Product>{
    @Override
    public int compare(Product x, Product y) {
        return Double.compare(x.getPrice(), y.getPrice());
    }
}