
import java.util.Date;

public class Information {
    private String nume;
    private String prenume;
    private String email;
    private String phone;
    private Date date_of_birth;
    private String genre;
    private String[] languages;
    private String[] languages_level;

    public Information(String nume, String prenume, String email, String phone,
                       Date date_of_birth, String genre, String[] languages, String[] languages_level) {
        this.nume = nume;
        this.prenume = prenume;
        this.email = email;
        this.phone = phone;
        this.date_of_birth = date_of_birth;
        this.genre = genre;
        this.languages = languages;
        this.languages_level = languages_level;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public Date getDate_of_birth() {
        return date_of_birth;
    }

    public void setDate_of_birth(Date date_of_birth) {
        this.date_of_birth = date_of_birth;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public String[] getLanguages() {
        return languages;
    }

    public void setLanguages(String[] languages) {
        this.languages = languages;
    }

    public String[] getLanguages_level() {
        return languages_level;
    }

    public void setLanguages_level(String[] languages_level) {
        this.languages_level = languages_level;
    }
}
