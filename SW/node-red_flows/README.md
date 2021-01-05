# StableEnoughVersion 1.0:
## MainFlow:
MQTT node bekommt daten.
pieceofshitsoftware wandelt daten die in einem char array(dec. values) gefuellten daten und schreibt sie in ASCII um und fuellt die werte einzeln in eine liste.
DoWeKnowThisDevice generiert einen pfad der die position eines neu ankommenden ESPs in eine CSV Datei speichert. Die in ASCII umgewandelten werte werden parst usw... der code ist selbstverstaendlich. Es wird am schluss ein positionswert mitgeschickt am return
PosxListener wartet auf die jeweilige position ab und parst und schickt die werte an die jeweiligen text nodes.
## SetThresholds:
Der User definiert thresholds die schlussendlich indirekt die LEDs ansteuern. Die werte werden in files geschpeichrt und readlefilexxxMin/Max liest die werte aus den jeweiligen datein da nodered die werte beim neu aufstarten nicht speichert. VerifyTheThresholds schaut dass die Min werte nicht ueber den Max werten sind. Sonst wird ein error geschrieben.
## RGBControlling:
Die ausgehenden werte von DoWeKnowThisDevice werden mit den thresholds verglichen und dann jenachdem welcher ESP welchen wert unter/ueberschritten hat, wird eine LED mit verschiedenen farb angesteuert. Der rest sorgt dafuer, dass die LED nicht aufhoert zu blinken, solang die werte nicht in den thresholds sind. Grobe beschreibung aller nodes.
