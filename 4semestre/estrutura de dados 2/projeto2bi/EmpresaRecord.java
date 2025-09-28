import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class EmpresaRecord {
    private LocalDate periodo;
    private String naturezaJuridica;
    private String porte;
    private String municipio;
    private String bairro;
    private String operacao;
    private String cnae;
    private String descCnae;
    private int empresas;

    // Ponteiro para lista ligada (para uso nas árvores)
    public EmpresaRecord next;

    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("dd/MM/yyyy");

    public EmpresaRecord(String[] campos) {
        if (campos.length < 9) throw new IllegalArgumentException("Linha inválida: número insuficiente de campos");
        try {
            this.periodo = LocalDate.parse(campos[0].trim(), FORMATTER);
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Data inválida: " + campos[0]);
        }
        this.naturezaJuridica = campos[1] != null ? campos[1].trim() : "";
        this.porte = campos[2] != null ? campos[2].trim() : "";
        this.municipio = campos[3] != null ? campos[3].trim() : "";
        this.bairro = campos[4] != null ? campos[4].trim() : "";
        this.operacao = campos[5] != null ? campos[5].trim() : "";
        this.cnae = campos[6] != null ? campos[6].trim() : "";

        StringBuilder sb = new StringBuilder();
        for (int i = 7; i < campos.length - 1; i++) {
            if (i > 7) sb.append(";");
            sb.append(campos[i] != null ? campos[i].trim() : "");
        }
        this.descCnae = sb.toString();

        String ultimoCampo = campos[campos.length - 1];
        try {
            this.empresas = Integer.parseInt(ultimoCampo.trim());
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Número de empresas inválido: " + ultimoCampo);
        }
        this.next = null;
    }

    public LocalDate getPeriodo() { return periodo; }
    public String getMunicipio() { return municipio; }
    public String getNaturezaJuridica() { return naturezaJuridica; }
    public int getEmpresas() { return empresas; }
    public String getPorte() { return porte; }
    public String getCnae() { return cnae; }
    public String getDescCnae() { return descCnae; }

    @Override
    public String toString() {
        return String.format("[%s - %s - %s - %s - %d empresas]", 
            periodo, naturezaJuridica, porte, municipio, empresas);
    }
}