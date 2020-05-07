class Solution {
	public int solution(String s) {
		if(s.length() == 1)
			return 1;
		
		int minLen = Integer.MAX_VALUE;
		for(int unit = 1; unit <= s.length() / 2; unit++) {
			minLen = Integer.min(minLen, getCompressedLen(s, unit));
		}
		return minLen;
	}
	
	public static int getCompressedLen(String s, int unit) {
		int cLen = 0;
		int idx = 0;
		
		String std = null;
		int sameCount = 1;
		for(int cutCount = 0; cutCount < s.length() / unit; cutCount++) {
			String cut = s.substring(idx, idx + unit);
			if(std == null) {
				std = cut;
				idx += unit;
				continue;
			}
			
			if(cut.equals(std)) {
				sameCount++;
			} else {
				cLen += unit;
				if(sameCount != 1)
					cLen += String.valueOf(sameCount).length();
				
				std = cut;
				sameCount = 1;
			}
			
			idx += unit;
		}
		
		cLen += unit;
		if(sameCount != 1)
			cLen += String.valueOf(sameCount).length();
			
		
		cLen += s.length() % unit;
		return cLen;
	}
}