#include <iostream>
#include <vector>
using namespace std;
class LcgGenerator
{
    private:
    uint16_t mA;
    uint16_t mC;
    uint16_t mCurrentX;
    uint16_t mM;

    public:
    LcgGenerator(uint16_t A, uint16_t C, uint16_t currentX, uint16_t M)
    {
        mA = A;
        mC = C;
        mCurrentX = currentX;
        mM = M;
    }

    uint16_t next()
    {   mCurrentX=(mA * mCurrentX + mC)%mM;
        return mCurrentX;
    }


};

class Card
{
    private: string mSuite;
    uint16_t mValue;

    public:

    Card(const string & suite, uint16_t value)
    {
        mSuite = suite;
        mValue = value;
    }

    bool operator ==(const Card & P) const
    {
        return((P.mSuite==mSuite) && (P.mValue==mValue));
    }

    string toString()const
    {
        string carti;
         carti = to_string(mValue) + "," + mSuite;
        return carti;
    }
    string getSuite() const
    {
        return mSuite;
    }
    uint16_t getValue() const
    {
        return mValue;
    }

   bool isFake() const{
        if((mValue <2 || mValue>14)||(mSuite!="rosu" && mSuite!="negru" &&  mSuite!="trefla" && mSuite!="romb")) return true;
        return false;
    }

    uint16_t getBlackjackValue() const
    {
        if(mValue>=2 && mValue<=10)
          return mValue;
        else
           return 10;

    }


};

class CardPack
{
    private:
    vector <Card> mCards;
    uint16_t mCurrentIndex;

    public:

    int getSize()
    {
        return mCards.size();
    }
    CardPack(bool empty = 1)
    {
        mCurrentIndex = 0;
        if(empty==0)
    {
        for(int i=2;i<=14;i++)
        {
            if(i!=11)

        mCards.push_back(Card("rosu",i));
        }


        for(int i=2;i<=14;i++)
        {
            if(i!=11)

        mCards.push_back(Card("negru",i));
        }

        for(int i=2;i<=14;i++)
        {
            if(i!=11)

        mCards.push_back(Card("romb",i));
        }

        for(int i=2;i<=14;i++)
        {
            if(i!=11)

        mCards.push_back(Card("trefla",i));
        }
        }


    mCurrentIndex = 0;

    }

    bool goodForBackjack() const
    {
       for(int i=0;i<mCards.size();i++)
        {
            if(mCards[i].isFake()==true)
            {

                return false;
            }
        }

        return true;


    }

    bool ok() const
    {

        if(mCards.size()!=52) return false;
        for(int i=0;i<mCards.size();i++)
        {
            if(mCards[i].isFake()==true)
            {
                return false;

            }
        }
        int ok=0;
        for(int i=0;i<mCards.size()-1;i++)
        {
            for(int j=i+1;j<mCards.size();j++)
                if(mCards[i]==mCards[j])
                {
                    ok=1;
                }
        }
        if(ok==1)
        {
            return false;

        }
        else
        {

            return true;
        }
    }

    void addCard(const Card & carte)
    {   if(mCards.size()<52)
        mCards.push_back(carte);
    }

    Card getCard(int x)
   {
        return mCards[x];
   }
      void shuffle(uint16_t a1,uint16_t c1, uint16_t x01, uint16_t a2, uint16_t c2, uint16_t x02)
    {  uint16_t x1,x2;
        LcgGenerator A(a1,c1,x01,mCards.size());
        LcgGenerator B(a2,c2,x02, mCards.size());
        x1 = A.next();
        x2 = B.next();
        Card C = Card(mCards[x1]);
        mCards[x1] = mCards[x2];
        mCards[x2] = C;



        mCurrentIndex = 0;

    }

    void printPack() const
    {
        for(int i=0;i<mCards.size();i++)
        {
            cout<<mCards[i].Card::toString()<<endl;
        }
    }
    Card nextCard()
    {
        return mCards[mCurrentIndex];
       mCurrentIndex++;
    }


};

class Player
{
public:
    string mName;
    uint16_t mMoney;
    uint16_t mPoints;

    Player(string name, uint16_t money)
    {
        mName = name;
        mMoney = money;
        mPoints = 0;

    }

    Player()
    {
        mName = "Dealer";
        mMoney = 0;
        mPoints = 0;
    }
    string toString() const
    {
        string prop;
        prop = mName+": "+ to_string(mMoney);
        return prop;
    }

    void pick(const Card & A)
    {
        if(A.getValue()>=2 && A.getValue()<=10)
        {
            mPoints  = mPoints +  A.getValue();
        }
        else
            mPoints = mPoints + 10;
    }
    void play( CardPack & pachet)
    {
        while (mPoints <17)
        {

                mPoints= mPoints + pachet.nextCard().getBlackjackValue();

        }
    }

    void newRound()
    {
        mPoints = 0;
    }

    bool lostRound() const
    {
        if(mPoints>21)
            return true;
        return false;
    }
    uint16_t getPoints() const
    {
        return mPoints;
    }
    void operator --()
    {
        mMoney = mMoney - 10;
    }
    void operator ++()
    {
        mMoney = mMoney + 10;
    }

    bool lostGame() const
    {
        if(mMoney <10)
            return true;
        return false;
    }



};


int main()
{  string command;

    vector<Player> jucatori;
    CardPack  pachet;
    int generator[30];
    uint16_t numar_carte;
    string stema_carte;
    string nume;
    int n;
    Player dealer;
    uint32_t suma_bani;
    uint16_t a1,a2,c1,c2,x01,x02;
    cin>>command;
    char virgula[2];
    if(command == "check_cards")
    {
        while(cin>>numar_carte)
        {
            cin>>virgula[0]>>stema_carte;

            pachet.addCard( Card(stema_carte, numar_carte));

        }




       if( pachet.goodForBackjack()==true)
        {  if(pachet.ok()==true)
        cout<<"Pachet OK"<<endl;
        else
        cout<<"Pregatit pentru Blackjack"<<endl;
        }
        else
        cout<<"Pachet masluit"<<endl;



    }


    if(command == "shuffle_cards")
    {  uint16_t a,b;

       cin>> a1>>c1>>x01;
        cin>> a2>>c2>>x02;

        while(cin>>numar_carte)
        {   cin>>virgula[0];
            cin >> stema_carte;
            pachet.addCard( Card(stema_carte, numar_carte));
        }
         uint16_t m=pachet.getSize();





        for(int i=0;i<50;i++)
        {
        LcgGenerator A(a1,c1,x01,m);
        LcgGenerator B(a2,c2,x02, m);
        pachet.shuffle(a1,c1,x01,a2,c2,x02);
        x01 = A.next();
        x02 = B.next();



        }
        pachet.printPack();


    }

    if(command == "play_game")
     {
         int n;
         cin>>n;
         for(int i=0;i<n;i++)
         {
             cin>>nume>>suma_bani;
             jucatori.push_back(Player(nume,suma_bani));

         }
         pachet = CardPack(0);
         int k ;
         uint16_t m=pachet.getSize();


         while(cin>>a1>>c1>>x01>>a2>>c2>>x02)
         {




        for(int i=0;i<50;i++)
        {
        LcgGenerator A(a1,c1,x01,m);
        LcgGenerator B(a2,c2,x02, m);

        pachet.shuffle(a1,c1,x01,a2,c2,x02);
        x01 = A.next();
        x02 = B.next();



        }



             k=0;
             for(int i=0;i<n;i++)
             {
                 jucatori[i].pick(pachet.getCard(k));
                 k++;
                 jucatori[i].pick(pachet.getCard(k));
                 k++;

             }
             dealer.pick(pachet.getCard(k));
             k++;
             dealer.pick(pachet.getCard(k));
             k++;
             for(int i=0;i<n;i++)
             {
                 while(jucatori[i].getPoints()<17)
                { jucatori[i].pick(pachet.getCard(k));
                k++;}


             }
            while(dealer.getPoints()<17)
            {
                dealer.pick(pachet.getCard(k));
                k++;
            }
             if(dealer.lostRound()==false)
             {
                 for(int i=0;i<n;i++)
                    { if(jucatori[i].getPoints()>dealer.getPoints() && jucatori[i].lostRound()==false) {
                        ++jucatori[i];
                     }
                 else
                 {if(jucatori[i].getPoints()< dealer.getPoints() || jucatori[i].getPoints()>21 )
                 {

                     --jucatori[i];
                 }

                    }

             }}
             else
             {  for(int i=0;i<n;i++)
                 {if(jucatori[i].lostRound()==false)

                     ++jucatori[i];
                 else
                     --jucatori[i];
                 }
             }
             int p = n;
             for(int i=0;i<p;i++)
             {
                 if(jucatori[i].lostGame()==true)
                 {
                     jucatori.erase(jucatori.begin()+i);
                     n--;

                 }
             }

             for(int i=0;i<n;i++)
             {
                 jucatori[i].newRound();
             }
             dealer.newRound();


         }

         for(int i=0;i<n;i++)
           cout<<jucatori[i].toString()<<endl;


     }


    return 0;
}