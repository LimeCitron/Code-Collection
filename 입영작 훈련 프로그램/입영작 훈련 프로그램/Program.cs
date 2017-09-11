using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text;

namespace 입영작_훈련_프로그램
{
    static class Program
    {
        /// <summary>
        /// 해당 응용 프로그램의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

        }
    }

    class Set
    {
        public string kor;
        public string eng;
    }

    class Unit
    {
        List<string> kor;
        List<string> eng;
        int unit_code;
        int unit_count;

        public int UnitCode
        {
            get { return this.unit_code; }
        }

        public int UnitCount
        {
            get { return unit_count; }
        }

        public string Kor(int num)
        {
            return kor[num];
        }

        public string Eng(int num)
        {
            return eng[num];
        }

        public Unit()
        {
            unit_code = -1;
        }
        public Unit(FileInfo fi, int code)
        {
            unit_code = code;
            FileStream fs = fi.OpenRead();
            StreamReader sr = new StreamReader(fs, System.Text.Encoding.GetEncoding("ks_c_5601-1987"));
            kor = new List<string>();
            eng = new List<string>();

            while(true)
            {
                string a = sr.ReadLine();
                if(a == null)
                {
                    break;
                }
                kor.Add(a);
                a = sr.ReadLine();
                eng.Add(a);
            }

            unit_count = kor.Count();
        }       
    }

    class LibraryBuilder
    {
        List<Unit> unitlist;
        public List<Unit> UnitList
        {
            get { return unitlist; }
        }

        public LibraryBuilder()
        {
            string Path = AppDomain.CurrentDomain.BaseDirectory + @"\sentences\";
            unitlist = new List<Unit>();
            int code;
            DirectoryInfo di = new DirectoryInfo(Path);
            if (di.Exists == false)
            {
                di.Create();
            }     

            foreach(var item in di.GetFiles())
            {
                string name = item.Name;
                Int32.TryParse(name.Substring(0, 3), out code);
                var NewUnit = new Unit(item, code);
                unitlist.Add(NewUnit);
            }
        }
    }

    class Selecter
    {
        List<Unit> unitlist;
        int selected_unit;
        int selected_sent;
        int counted_unit;
        public Selecter() { }

        public Selecter(LibraryBuilder lb)
        {
            unitlist = new List<Unit>();
            counted_unit = lb.UnitList.Count;
            this.unitlist = lb.UnitList;
        }

        public Set SelectSentence()
        {
            var temp = new Set();
            Random r = new Random();
            selected_unit = r.Next(0, counted_unit);
            selected_sent = r.Next(0, unitlist[selected_unit].UnitCount);

            temp.kor = unitlist[selected_unit].Kor(selected_sent);
            temp.eng = unitlist[selected_unit].Eng(selected_sent);
            return temp;
        }
    }
}
