import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;
/*
 * 5397_키로거 시간초과
 * 
 * main() -> getPwd()
 * 
 * 처음에 pwd = "", cursor = 0으로 놓은 뒤 
 * 1. < : 맨 왼쪽에 있을 때 빼고 cursor--
 * 2. > : 그 반대.
 * 3. - : 맨 왼쪽일 때 빼고 현재 커서의 왼쪽 문자 지움 (cursor--) -> 연속되면 한번에지움
 * 4. 그 외 : 현재 커서에 문자 insert (cursor++) -> 연속되면 한번에 추가
 */
public class Main2 {
	static int T;
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		while(T-- > 0) {
			String s = br.readLine();
			System.out.println(getPwd(s));
		}
	}
	
	static StringBuffer getPwd(String s) {
		StringBuffer pwd = new StringBuffer("");
		int cursor = 0;
		for(int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			
			if(c == '<') {
				if(cursor > 0)
					cursor--;
			} else if(c == '>') {
				if(cursor < pwd.length())
					cursor++;
			} else if(c == '-') {
				if(cursor == 0)
					continue;
				
				int erase = 1;
				while(true) {
					i++;
					if(i == s.length())
						break;
					
					c = s.charAt(i);
					if(c != '-')
						break;
					
					erase++;
				}
				i--;
				pwd.delete(Integer.max(cursor - erase, 0), cursor);
				cursor -= erase;
				if(cursor < 0)
					cursor = 0;
			} else {
				String st = String.valueOf(c);
				while(true) {
					i++;
					if(i == s.length())
						break;
					
					c = s.charAt(i);
					if(c == '<' || c == '>' || c == '-')
						break;
					
					st += c;
				}
				i--;
				pwd.insert(cursor, st);
				cursor += st.length();
			}
		}
		return pwd;
	}
}