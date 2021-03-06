#include "musicbarragerecordconfigmanager.h"

MusicBarrageRecordConfigManager::MusicBarrageRecordConfigManager(QObject *parent)
    : MusicAbstractXml(parent)
{

}

void MusicBarrageRecordConfigManager::writeBarrageConfig(const MusicBarrageRecords &records)
{
    if(!writeConfig(BARRAGEPATH_FULL))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement musicPlayer = createRoot(APPNAME);
    QDomElement download = writeDom(musicPlayer, "barrageRecord");

    foreach(const MusicBarrageRecord &record, records)
    {
        writeDomElementMutilText(download, "value", MusicXmlAttributes() << MusicXmlAttribute("color", record.m_color)
                                 << MusicXmlAttribute("size", record.m_size), record.m_value);
    }

    //Write to file
    QTextStream out(m_file);
    m_document->save(out, 4);
}

void MusicBarrageRecordConfigManager::readBarrageConfig(MusicBarrageRecords &records)
{
    QDomNodeList nodelist = m_document->elementsByTagName("value");
    for(int i=0; i<nodelist.count(); ++i)
    {
        MusicBarrageRecord record;
        record.m_color = nodelist.at(i).toElement().attribute("color");
        record.m_size = nodelist.at(i).toElement().attribute("size").toInt();
        record.m_value = nodelist.at(i).toElement().text();
        records << record;
    }
}
