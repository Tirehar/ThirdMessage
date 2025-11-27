using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using ThirdMessage.ServierAPI.Database.Entitys;

namespace ThirdMessage.ServierAPI.Database.EntityConfigs;

public class MessageEntityConfig : IEntityTypeConfiguration<MessageEntity>
{
    public void Configure(EntityTypeBuilder<MessageEntity> builder)
    {
        builder.ToTable("Messages");
        builder.HasKey(x => x.Id);
    }
}
