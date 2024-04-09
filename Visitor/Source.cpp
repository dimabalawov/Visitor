#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Processor;
class Hdd;
class GPU;
class RAM;

class IVisitor abstract
{
public:
	virtual void VisitProcessor(Processor* proc) abstract;
	virtual void VisitHdd(Hdd* hdd) abstract;
	virtual void VisitGPU(GPU* gpu) abstract;
	virtual void VisitRAM(RAM* ram) abstract;
};

class AbstractDevice abstract
{
	string Producer;
public:
	virtual void Accept(IVisitor* visitor)abstract;
	string GetProducer()
	{ 
		return Producer;
	}
	void SetProducer(string Producer)
	{
		this->Producer = Producer;
	}
};

class Processor: public AbstractDevice
{
	string Frequency;
	string CoreCount;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetCoreCount()
	{
		return CoreCount;
	}
	void SetCoreCount(string CoreCount)
	{
		this->CoreCount = CoreCount;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitProcessor(this);
	}
};

class Hdd: public AbstractDevice
{
	string Volume;
	string Type;
public:
	string GetVolume()
	{
		return Volume;
	}
	void SetVolume(string Volume)
	{
		this->Volume = Volume;
	}
	string GetType()
	{
		return Type;
	}
	void SetType(string Type)
	{
		this->Type = Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitHdd(this);
	}
};

class GPU : public AbstractDevice
{
	string chipset;
	string memory;
public:
	string GetChipset()
	{
		return chipset;
	}
	void SetСhipset(string chipset)
	{
		this->chipset = chipset;
	}
	string GetMemory()
	{
		return memory;
	}
	void SetMemory(string memory)
	{
		this->memory = memory;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitGPU(this);
	}
};

class RAM : public AbstractDevice
{
	string memory;
	string frequency;
public:
	string GetMemory()
	{
		return memory;
	}
	void SetMemory(string memory)
	{
		this->memory = memory;
	}
	string GetFrequency()
	{
		return frequency;
	}
	void SetFrequency(string frequency)
	{
		this->frequency = frequency;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitRAM(this);
	}
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + proc->GetProducer() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + proc->GetFrequency() + "</td></tr>";
		result += "<tr><td>CoreCount<td><td>" + proc->GetCoreCount() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + hdd->GetProducer() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + hdd->GetType() + "</td></tr>";
		result += "<tr><td>Volume<td><td>" + hdd->GetVolume() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitGPU(GPU* gpu) override
	{
		ofstream out("GPU.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + gpu->GetProducer() + "</td></tr>";
		result += "<tr><td>Chipset<td><td>" + gpu->GetChipset() + "</td></tr>";
		result += "<tr><td>Memory<td><td>" + gpu->GetMemory() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + ram->GetProducer() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + ram->GetFrequency() + "</td></tr>";
		result += "<tr><td>Memory<td><td>" + ram->GetMemory() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в XML
class XmlVisitor: public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<Processor><Producer>" + proc->GetProducer() + "</Producer>" +
			"<Frequency>" + proc->GetFrequency() + "</Frequency>" +
			"<CoreCount>" + proc->GetCoreCount() + "</CoreCount></Processor>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<HDD><Producer>" + hdd->GetProducer() + "</Producer>" +
			"<Type>" + hdd->GetType() + "</Type>" +
			"<Volume>" + hdd->GetVolume() + "</Volume></HDD>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitGPU(GPU* gpu) override
	{
		ofstream out("GPU.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<GPU><Producer>" + gpu->GetProducer() + "</Producer>" +
			"<Chipset>" + gpu->GetChipset() + "</Chipset>" +
			"<Memory>" + gpu->GetMemory() + "</Memory></GPU>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<RAM><Producer>" + ram->GetProducer() + "</Producer>" +
			"<Frequency>" + ram->GetFrequency() + "</Frequency>" +
			"<Memory>" + ram->GetMemory() + "</Memory></RAM>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};
class TextVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.txt", ios::trunc | ios::out);
		string result = "Producer: " + proc->GetProducer() + "\n" + "Frequency: " + proc->GetFrequency() + "\n" + "Cores: " + proc->GetCoreCount() + "\n\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("HDD.txt", ios::trunc | ios::out);
		string result = "Producer: " + hdd->GetProducer() + "\n" + "Volume: " + hdd->GetVolume() + "\n" + "Type: " + hdd->GetVolume() + "\n\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitGPU(GPU* gpu) override
	{
		ofstream out("GPU.txt", ios::trunc | ios::out);
		string result = "Producer: " + gpu->GetProducer() + "\n" + "Chipset: " + gpu->GetChipset() + "\n" + "Memory: " + gpu->GetMemory() + "\n\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.txt", ios::trunc | ios::out);
		string result = "Producer: " + ram->GetProducer() + "\n" + "Frequency: " + ram->GetFrequency() + "\n" + "Memory: " +ram->GetMemory() + "\n\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

class ConsoleVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		cout << "Processo Info:\n";
		cout << "Producer: " << proc->GetProducer() << "\n";
		cout << "Frequency: " << proc->GetFrequency() << "\n";
		cout << "Cores: " << proc->GetCoreCount() << "\n\n";
	}
	void VisitHdd(Hdd* hdd) override
	{
		cout << "HDD Info:\n";
		cout << "Producer: " << hdd->GetProducer() << "\n";
		cout << "Volume: " << hdd->GetVolume() << "\n";
		cout << "Type: " << hdd->GetType() << "\n\n";
	}
	void VisitGPU(GPU* gpu) override
	{
		cout << "GPU Info:\n";
		cout << "Producer: " << gpu->GetProducer() << "\n";
		cout << "Chipset: " << gpu->GetChipset() << "\n";
		cout << "Memory: " << gpu->GetMemory() << "\n\n";
	}
	void VisitRAM(RAM* ram) override
	{
		cout << "RAM Info:\n";
		cout << "Producer: " << ram->GetProducer() << "\n";
		cout << "Frequency: " << ram->GetFrequency() << "\n";
		cout << "Memory: " << ram->GetMemory() << "\n\n";
	}
};

class PC
{
	vector<AbstractDevice*> devices;
public:
	void Add(AbstractDevice* d)
	{
		devices.push_back(d);
	}
	void Remove(AbstractDevice* d)
	{
		auto iter = find(devices.begin(), devices.end(), d);
		if(iter != devices.end())
			devices.erase(iter);
	}
	void Accept(IVisitor* visitor)
	{
		for(AbstractDevice* d : devices)
			d->Accept(visitor);
	}
};

int main()
{
	PC* pc = new PC();
	Processor *p = new Processor;
	p->SetProducer("Intel");
	p->SetFrequency("3.5");
	p->SetCoreCount("4");
	pc->Add(p);
	Hdd *hdd = new Hdd;
	hdd->SetProducer("Western Digital");
	hdd->SetType("SATA III");
	hdd->SetVolume("2");
	pc->Add(hdd);
	GPU* gpu = new GPU;
	gpu->SetProducer("Nvidia");
	gpu->SetСhipset("GTX 3060TI");
	gpu->SetMemory("8GB");
	pc->Add(gpu);
	RAM* ram = new RAM;
	ram->SetProducer("Kingston");
	ram->SetMemory("16GB");
	ram->SetFrequency("3200MHz");
	HtmlVisitor *html = new HtmlVisitor;
	pc->Accept(html);
	XmlVisitor *xml = new XmlVisitor;
	pc->Accept(xml);
	TextVisitor* text = new TextVisitor;
	pc->Accept(text);
	ConsoleVisitor* console = new ConsoleVisitor;
	pc->Accept(console);
	delete html;
	delete text;
	delete console;
	delete xml;
	delete hdd;
	delete ram;
	delete gpu;
	delete p;
	delete pc;

	system("pause");
}
