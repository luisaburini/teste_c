 # Questão 04

  Dada uma array de k , lista lincada “listas”, cada lista esta em ordem ascendente. 
  Mergear as listas lincadas em uma única lista em ordem ascendente.
  
  Input:
  ```
  listas = [[1,3,8],[1,3,6],[8,9]] 
  ```

  Output:
  ```
  [1,1,3,3,6,8,8,9]
  ```
  
  Referência:
  ```
  listas = [ ] 
  output = [ ]
  listas = [ [ ] ] 
  output = [ ]
  struct ListaNode* mergeKListas(struct ListNode** listas, int listasSize){}
  ```

  o programa foi compilado com a linha de comando
  ```
   gcc -g -o mergeLists mergeLists.c 
  ```

  para usar invoque
  ```
  ./mergeLists 
  ```

  Digite na entrada padrão a lista desejada
  ```
  # Exemplo
  [[1, 4, 7], [2, 5, 8], [3, 6, 9]]
  ```
  
  A resposta será impressa na saída padrão