// Sin pérdida de generalidad, supongamos que el arreglo está ordenado de menor a mayor.
// Para encontrar el máximo, debemos devolver el último elemento del arreglo. Al estar ordenado, el encontrar un máximo es más sencillo.
// Para encontrar el mínimo, debemos devolver el primer elemento del arreglo. Nuevamente, como está ordenado, econtrar el mínimo es más sencillo.
// Si el arreglo tiene una cantidad impar de números, para hallar la mediana debemos devolver el elemento que se encuentra en la posición n / 2, siendo n la longitud del arreglo. Si tiene una cantidad par de elementos, debemos devolver ((n / 2) - 1 + (n / 2)) / 2, donde n es la longtid del arreglo. En este caso, como el arreglo está ordenado, nos ahorramos tener que ordenarlo antes de hallar los valores.
