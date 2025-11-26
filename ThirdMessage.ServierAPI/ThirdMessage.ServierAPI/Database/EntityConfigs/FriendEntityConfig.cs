using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using ThirdMessage.ServierAPI.Database.Entitys;

namespace ThirdMessage.ServierAPI.Database.EntityConfigs;

public class FriendEntityConfig : IEntityTypeConfiguration<FriendEntityl>
{
    public void Configure(EntityTypeBuilder<FriendEntityl> builder)
    {
        builder.ToTable("Friends");
        builder.HasKey(f => f.FriendId);
        builder.Property(f => f.Uid).HasMaxLength(50).IsRequired();
        builder.Property(f => f.FriendId).HasMaxLength(100).IsRequired();
        builder.Property(f => f.UserName).HasMaxLength(50).IsRequired();
    }
}
