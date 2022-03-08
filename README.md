# Ogrenci Kayit Sistemi

## İçindekiler:

    Not - Bilgilendirme

    Öğrenciyle İlgili Fonksiyonlar:
        Öğrenci Ekleme
        Öğrenci Silme
        Derse Kaydolma
        Dersi Bırakma

    Dersle İlgili Fonksiyonlar:
        Ders Ekleme
        Ders Silme

    Yazdırmayla İlgili Fonksiyonlar:
        İstenilen Öğrenciye Ait Derslerin Yazdırılması
        İstenilen Derse Ait Öğrencilerin Yazdırılması

## Notlar - Bilgilenerdirme:

Program ilk açıldığında kullanıcıdan bir öğrencinin alabileceği maksimum kredi sayısı ile maksimum ders sayısını kullanıcıdan ister ve bu sayı program yeniden çalıştırılana kadar değiştirilemez.

Ders kodlarının karşılaştırmalarında büyük küçük harf ayrımı vardır. Yani BLM1012 diye kaydedilen derse blm1012 diye erişilmeye çalışılırsa ders bulunamadı uyarısı verir. 

Terminal önceki çıktıların da görülebilmesi için temizlenmemiştir.

Programı Ctrl-C ile değil de ana menüden 12 girdisi verilerek sonlandırılırsa programın ramde kullandığı hafıza alanı free fonksiyonu ile temizlenir. O yüzden programı ana menüden sonlandırınız. 

Eğer öğrenci dersi bırakırsa veya öğrenci silinirse, aldığı bütün derslerin durumu birakti olarak güncelleniyor. Ana proje açıklamasında birakti yapın yazıyor ama bize verilen yapısalInput adlı dosyanın içindeki OgrenciDersKayit.txt dosyasının içinde silindi yapılmış. Bana birakti durumu daha mantıklı geldiği için verilen input dosyasını güncelledim ve artık birakti yazdırılıyor.


## Öğrenciyle İlgili Fonksiyonlar:

### Öğrenci Ekleme:

Bu fonksiyonun amacı tek yönlü linked list şeklinde oluşturulmuş öğrenciler listesinin içine öğrenci eklemek sonra ögrenciler.txt dosyası oluşturulmuşsa onu güncellemek, oluşturulmamışsa dosyayı oluşturup bütün öğrencileri içine eklemektir. Ekleme işlemini kontrol etmek için List Students fonksiyonu oluşturulmuştur. Bu fonksiyon öğrenciler linked listindeki bütün öğrencileri yazdırmakla görevlidir.

Nasıl Çalıştırıldığı:

İlk başta menüden add student seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 1 giriyoruz. Sonra bizden öğrenci adı, soyadı ve numarasını istiyor. Bunları doldurduktan sonra eğer öğrenci eklenebildiyse  “Student (Öğrenci_Numarası) Succesfully Added” mesajını gösteriyor. Eğer aynı numaradan başka bir öğrenci varsa da uyarı veriyor. Bunları yaptıktan sonra da ogrenci.txt dosyasını güncelliyor.

### Öğrenci Silme:

Bu Fonksiyonun amacı öğrenci numarası verilen ve öğrenci linkli listesinde tutulan öğrenciyi listeden çıkartmaktır. Öğrenci listeden çıkartılınca ogrenci.txt dosyası güncellenir. Eğer numarası verilen öğrenci listede yoksa uyarı mesajı gösterilir. Kontrol için List Students fonksiyonu kullanılmıştır.

Nasıl Çalıştırıldığı:

İlk başta menüden Delete Student seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 2 giriyoruz. Sonra bizden öğrencinin numarasını istiyor. Bunları doldurduktan sonra eğer öğrenci silinebildiyse  “Student With Number (Öğrenci Numarası) is Sucessfully Deleted” mesajını gösteriyor. Eğer öğrenci linkli listede bulunmuyorsa uyarı mesajı veriyor. Bunları yaptıktan sonra da ogrenci.txt dosyasını güncelliyor.

### Derse Kaydolma:

Bu fonksiyonun amacı tek yönlü linkli liste şeklinde oluşturulmuş öğrenciDersKayıt listesinin içine durum eklemek sonra ÖğrenciDersKayıt.txt dosyası oluşturulmuşsa onu güncellemek, oluşturulmamışsa dosyayı oluşturup bütün dersleri içine yazdırmaktır. Diğer bir amacı da dersler linkli listesinde kaydolmak istenilen dersi bulmak ve onun öğrenci numaralarını tutan listesinin içine kaydolmak isteyen öğrencinin numarasını eklemektir.  Ekleme işlemini kontrol etmek için List Status fonksiyonu oluşturulmuştur. Bu fonksiyon öğrenciDersKayıt linkli listesindeki bütün durumları yazdırmakla görevlidir.


Nasıl Çalıştırıldığı:

İlk başta menüden Enroll To a Lesson seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 5 giriyoruz. Sonra bizden kaydolmak isteyen öğrencinin numarasını, dersin kodunu ve tarihi istiyor. Bunları doldurduktan sonra eğer derse kaydolunabilindiyse “Student (Öğrenci Numarası), succesfully enrolled to lesson (Ders Kodu)” mesajını gösteriyor. Eğer kodu verilen ders, dersler linkli listesinde bulunmuyorsa, numarası verilen öğrenci, öğrenciler linkli listesinde bulunmuyorsa veya öğrencinin o derse kaydı varsa uyarı mesajı veriyor. Eğer başarılı bir şekilde kaydolunursa OgrenciDersKayit.txt dosyası güncelleniyor. Aynı zamanda derse kaydolan öğrencinin numarası, aldığı dersin öğrenci numaralarının tutulduğu listeye de ekleniyor.

### Dersi Bırakma:

Bu fonksiyonun amacı tek yönlü linkli liste şeklinde oluşturulmuş öğrenciDersKayıt listesinin içine durum eklemek sonra ÖğrenciDersKayıt.txt dosyası oluşturulmuşsa onu güncellemek, oluşturulmamışsa dosyayı oluşturup bütün dersleri içine yazdırmaktır. Diğer bir amacı da dersler linkli listesinde bırakılmak istenilen dersi bulmak ve onun öğrenci numaralarını tutan listesinin içinden dersi bırakmak isteyen öğrencinin numarasını çıkartmaktır.  Ekleme işlemini kontrol etmek için List Status fonksiyonu oluşturulmuştur. Bu fonksiyon öğrenciDersKayıt linkli listesindeki bütün durumları yazdırmakla görevlidir.


Nasıl Çalıştırıldığı:

İlk başta menüden Withdraw From a Lesson seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 6 giriyoruz. Sonra bizden dersi bırakmak isteyen öğrencinin numarasını ve dersin kodunu istiyor. Bunları doldurduktan sonra eğer öğrencinin o derse kaydı varsa ve kaydı başarılı bir şekilde “kayitli” durumundan “birakti” durumuna geçirilebildiyse “Student (Öğrenci Numarası), Succesfully Withdraw From Lesson (Ders Kodu)” mesajını gösteriyor. Eğer kodu verilen ders, dersler linkli listesinde bulunmuyorsa, numarası verilen öğrenci, öğrenciler linkli listesinde bulunmuyorsa veya öğrencinin o derse kaydı yoksa uyarı mesajı veriyor. Eğer başarılı bir şekilde dersi bırakma işlemi yapılabilindiyse OgrenciDersKayit.txt dosyası güncelleniyor. Aynı zamanda dersi bırakan öğrencinin numarası, bıraktığı dersin öğrenci numaralarının tutulduğu listeden de çıkartılıyor.



## Dersle İlgili Fonksiyonlar:


### Ders Ekleme:

Bu fonksiyonun amacı çift yönlü linkli liste şeklinde oluşturulmuş dersler listesinin içine öğrenci eklemek sonra dersler.txt dosyası oluşturulmuşsa onu güncellemek, oluşturulmamışsa dosyayı oluşturup bütün dersleri içine yazdırmaktır. Ekleme işlemini kontrol etmek için List Lessons fonksiyonu oluşturulmuştur. Bu fonksiyon dersler linkli listesindeki bütün dersleri yazdırmakla görevlidir.


Nasıl Çalıştırıldığı:

İlk başta menüden Add Lesson seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 3 giriyoruz. Sonra bizden dersin kodunu, dersin adını, dersin kredisini ve dersin kontenjanını istiyor. Bunları doldurduktan sonra eğer ders eklenebildiyse  “Lesson (Ders Kodu) is Succesfully Added” mesajını gösteriyor. Eğer kodu verilen ders linkli listede bulunuyorsa da uyarı mesajı veriyor. Bunları yaptıktan sonra da dersler.txt dosyasını güncelliyor.

### Ders Silme:

Bu Fonksiyonun amacı ders kodu verilen ve dersler linkli listesinde tutulan dersi listeden çıkartmaktır. Ders listeden çıkartılınca dersler.txt dosyası güncellenir. Eğer numarası verilen ders listede yoksa uyarı mesajı gösterilir. Kontrol için List Lessons fonksiyonu kullanılmıştır. Eğer ders silinebilirse, OgrenciDersKayit linkli listesinde o dersin bulunduğu ve “kayitli” gösterilen bütün durumlar “ders silindi” durumuna alınır. Sonra OgrenciDersKayit.txt dosyası güncellenir. 

Nasıl Çalıştırıldığı:

İlk başta menüden Delete Lesson seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 4 giriyoruz. Sonra bizden dersin kodunu istiyor. Bunları doldurduktan sonra eğer ders  silinebildiyse  “Student With Number (Öğrenci Numarası) is Sucessfully Deleted” mesajını gösteriyor. Eğer ders linkli listede bulunmuyorsa uyarı mesajı veriyor. Bunları yaptıktan sonra da dersler.txt ve OgrenciDersKayit.txt dosyalarını güncelliyor.


## Yazdırmayla İlgili Fonksiyonlar:

### İstenilen Derse Ait Öğrencilerin Yazdırılması:

Bu Fonksiyonun amacı ders kodu verilen ders eğer dersler linkli listesinde bulunuyorsa ve dersi alan öğrenci varsa derskodu.txt dosyası oluşturmak ve içine bu dersi alan bütün öğrencilerin bilgilerini yazdırmaktır. 

Nasıl Çalıştırıldığı:

İlk başta menüden List Students of a Particular Lesson seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 8 giriyoruz. Sonra bizden dersin kodunu istiyor. Bunu doldurduktan sonra eğer istenilen ders dersler linkli listesinde bulunuyorsa ve öğrenci sayısı sıfırdan büyükse “The List Has Been Created” mesajını gösteriyor. Eğer ders linkli listede bulunmuyorsa veya öğrenci sayısı sıfırsa uyarı mesajı veriyor. Bunları yaptıktan sonra da DERSKODU.txt dosyası oluşturuyor ve içine o dersi alan öğrencilerin bilgilerini yazıyor.

### İstenilen Öğrenciye Ait Derslerin Yazdırılması:

Bu fonksiyonun amacı numarası verilen öğrenci eğer öğrenciler linkli listesinde bulunuyorsa ve aldığı ders varsa öğrenciNumarası_DERSPROGRAMI.txt dosyası oluşturmak ve içine öğrencinin aldığı bütün derslerin bilgilerini yazdırmaktır. 

Nasıl Çalıştırıldığı:

İlk başta menüden List Lessons of a Particular Student seçeneğini seçmemiz gerekiyor. Bunun için “Enter Your Choice: ” kısmına 7 giriyoruz. Sonra bizden öğrencinin numarasını istiyor. Bunu doldurduktan sonra eğer numarası verilen öğrenci, öğrenciler linkli listesinde bulunuyorsa ve aldığı ders sayısı sıfırdan büyükse “The List Has Been Created” mesajını gösteriyor. Bunları yaptıktan sonra da öğrenciNumarası_DERSPROGRAMI.txt  dosyası oluşturuyor ve içine öğrencinin aldığı derslerin bilgilerini yazıyor. Eğer öğrenci linkli listede bulunmuyorsa veya aldığı ders sayısı sıfırsa uyarı mesajı veriyor. 

