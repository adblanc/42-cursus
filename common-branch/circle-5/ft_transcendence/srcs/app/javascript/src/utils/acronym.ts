function checkListAng(list: string[], acronym: string) {
  if (!acronym) return 1;

  for (let i in list) {
    if (acronym === list[i]) {
      return 1;
    }
  }
  return 0;
}

function generate(name: string, rd: number) {
  let n: number = name.length;
  var spl = name.split(" ");
  let acronym: string = "";

  //use second letter or third letter, or second/third before last
  if (spl.length === 1) {
    acronym = acronym + name[0].toUpperCase();
    if (
      rd != 0 &&
      name[rd] != undefined &&
      name[rd] != name[Math.floor(n / 2)]
    ) {
      acronym += name[rd].toUpperCase();
      acronym += name[Math.floor(n / 2)].toUpperCase();
      acronym += name[n - 1].toUpperCase();
    } else if (rd != 0) {
      acronym += name[Math.floor(n / 2)].toUpperCase();
      acronym += name[n - 1 - rd].toUpperCase();
    } else {
      acronym += name[Math.floor(n / 2)].toUpperCase();
      acronym += name[n - 1].toUpperCase();
    }
    return acronym;
  }

  //add second or third letter of second word, or first if impossible
  if (spl.length === 2) {
    for (let i in spl) {
      acronym += spl[i][0].toUpperCase();
    }
    if (rd != 0 && spl[1][rd] != undefined && spl[1][rd] != spl[1][n - 1]) {
      acronym += spl[1][rd].toUpperCase();
    } else if (rd != 0 && spl[0][rd] != undefined) {
      acronym += spl[0][rd].toUpperCase();
    }
    n = spl[1].length;
    acronym += spl[1][n - 1].toUpperCase();
    return acronym;
  }

  let bool: boolean = false;
  let it: number = 0;

  //add second or third letter of second word, and then of third
  for (let i in spl) {
    acronym += spl[i][0].toUpperCase();
    if (it >= 2 && rd != 0) {
      n = spl[i].length - 1;
      acronym += spl[i][n].toUpperCase();
      n--;
    }
    if (it > 0 && rd != 0 && spl[i][rd] != undefined && bool == false) {
      acronym += spl[i][rd].toUpperCase();
      bool = true;
    }
    it++;
    if (acronym.length === 5) {
      break;
    }
  }
  return acronym;
}

export function generateAcn(name: string, list: string[]) {
  let acronym: string;
  let i: number = 0;

  while (checkListAng(list, acronym) == 1) {
    acronym = generate(name, i);
    //This is only if aglorithm fails 10 times so that we don't fall into infinite loop
    if (i >= 10) return "error";
    i++;
  }
  return acronym;
}
