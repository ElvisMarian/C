
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

abstract class Consumer {

    boolean visited;
    Resume resume;
    ArrayList<Consumer> cunoscuti;

    public void add(Education education) {
        if (this.resume.education.isEmpty())
            this.resume.education.add(education);

        for (int i = 0; i < this.resume.education.size(); i++) {
            if (this.resume.education.get(i).compareTo(education) < 0) {
                this.resume.education.add(i, education);
                return;
            }
        }
        this.resume.education.add(education);
    }

    public void add(Experience experience) {
        if (this.resume.experience.isEmpty())
            this.resume.experience.add(experience);

        for (int i = 0; i < this.resume.experience.size(); i++) {
            if (this.resume.experience.get(i).compareTo(experience) <= 0) {
                this.resume.experience.add(i, experience);
                return;
            }
        }
        this.resume.experience.add(experience);
    }

    public void add(Consumer consumer) {
        this.cunoscuti.add(consumer);
    }

    public void remove(Consumer consumer) {
        this.cunoscuti.remove(consumer);
    }

    public int getDegreeInFriendship(Consumer consumer) {

        ////BFS cu hashmap in care fiecare distanta de la this la consumer va fi tinuta in  hashmap
        Queue<Consumer> q = new LinkedList<>();
        HashMap<Consumer, Integer> distance = new HashMap<>();
        q.add(this);
        this.visited = true;
        while (q.isEmpty() == false) {
            for (int i = 0; i < q.peek().cunoscuti.size(); i++) {
                distance.put(q.peek().cunoscuti.get(i), distance.get(q.peek().cunoscuti.get(i - 1)) + 1);
                if (q.peek().cunoscuti.get(i).equals(consumer))
                    return distance.get(q.peek().cunoscuti.get(i));
                if (q.peek().cunoscuti.get(i).visited == false) {
                    q.peek().cunoscuti.get(i).visited = true;
                    q.add(q.peek().cunoscuti.get(i));
                }
            }
            q.poll();
        }
        return -1;
    }

    public Integer getGraduationYear() {
        return this.resume.education.get(0).end_date.getYear();
    }

    public Double meanGPA() {
        double result = 0;
        for (Education e : this.resume.education)
            result += e.grade;
        return result / (double) this.resume.education.size();
    }

    class Resume {
        Information info;
        ArrayList<Experience> experience;
        ArrayList<Education> education;
    }

}
