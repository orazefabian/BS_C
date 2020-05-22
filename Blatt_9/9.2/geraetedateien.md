

- Gerätedatei (von engl. device file) sind spezielle Dateien welche ermöglichen eine einfache Kommunikation zwischen Userspace und dem Kernel aufzubauen. 

- Block devices übertragen Daten in Datenblöcken und werden daher oft für parallele Datenübertragungen genutzt. Es wird ein Buffer genutzt. 

- Character devices übertragen nur ein Zeichen zur selben Zeit, sind also der seriellen Datenübertragung zuzusprechen. Meist, aber nicht immer, werden Daten ungepuffert übertragen.


- Die Major-Nummer gibt an, welcher Treiber zu diesem Gerät gehört. Der Kernel verwendet die Major-Nummer, um einem Gerät den passenden Treiber zuzuordnen.

- Die Minor-Nummer wird nur vom durch die Major-Nummer angegebenen Gerätetreiber benutzt; andere Teile des Kernels betrachten sie nicht und geben sie lediglich an den Treiber weiter. 

*auflisten von allen gerätedateien: ls -l /dev*

*/dev/random	character	major: 1	minor: 8*
*/dev/null	character	major: 1	minor: 3*

*sudo mknod testdev1 c 1 9  1 9 zeigt auf random*
*sudo mknod testdev2 c 1 5  1 5 zeigt auf dev/zero*

*xxd -l 20 testdev1*
*xxd -l 20 testdev2*



