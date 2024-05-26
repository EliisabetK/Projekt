# Projekt: API-ga retseptide otsimine
### Rühm AE: Liina Hoogand, Eliisabet Kaasik

### Projekti kasutamine:
1. Projekti jooksutada main.cpp failist
   
2. ### !!!Tähtis:
   Kuna kasutasime programmis libcurl teeki, siis on see projekti juurde lisatud, kuid alla laadimisel peab lisama arvutile system path environment variabledesse:
   "C:\Users\{user}\CLionProjects\Projekt\curl-8.7.1_7-win64-mingw\curl-8.7.1_7-win64-mingw\bin", et see õigesti tööle läheks.

3. Kui tuleb veateavitus "Process finished with exit code -1073741515 (0xC0000135), siis on ilmselt libcurlil path valesti määratud.
Pathi saab lisada nii: Environment Variables -> System variables -> Path -> New -> C:\Users\{user}\CLionProjects\Projekt\curl-8.7.1_7-win64-mingw\curl-8.7.1_7-win64-mingw\bin (kasutajanimi tuleb ära muuta)

4. Kui tekib makefilega probleem, siis võib proovida Invalidate Cashes -> Reset CMAKE Cache -> Invalidate and Restart (me mõlemad kasutasime CLionit, ma pole kindel kas vscodes on erinev see)

5. Jooksuta programmi ja juhised tulevad terminali/käsureale
