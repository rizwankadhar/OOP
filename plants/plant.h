#pragma once

class Plant
{
    protected:
        int _ripeningTime; ///érésiIdõ
        Plant(int i) : _ripeningTime(i) {}
    public:
        getRipeningTime() const { return _ripeningTime; }
        //virtual ~Plant() {}
        virtual bool isVegetable() const { return false; }
};

class Vegetable : public Plant ///Haszonnövény
{
    public:
        bool isVegetable() const override { return true; }

    protected:
        Vegetable(int i) : Plant(i) {}
};

class Flower : public Plant
{
    protected:
        Flower(int i) : Plant(i) {}
};

class Potatoe : public Vegetable
{
    public:
        static Potatoe* instance();
    private:
        Potatoe() : Vegetable(5) {}
        static Potatoe* _instance;
};

class Pea : public Vegetable
{
    public:
        static Pea* instance();
    private:
        Pea() : Vegetable(3) {}
        static Pea* _instance;
};

class Onion : public Vegetable
{
    public:
        static Onion* instance();
    private:
        Onion() : Vegetable(4) {}
        static Onion* _instance;
};

class Rose : public Flower
{
    public:
        static Rose* instance();
    private:
        Rose() : Flower(8) {}
        static Rose* _instance;
};

class Carnation : public Flower
{
    public:
        static Carnation* instance();
    private:
        Carnation() : Flower(10) {}
        static Carnation* _instance;
};

class Tulip : public Flower
{
    public:
        static Tulip* instance();
    private:
        Tulip() : Flower(7) {}
        static Tulip* _instance;
};
